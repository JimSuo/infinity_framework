#include "LuaStateSubsystem.h"

#include "ProfilingDebugging/CpuProfilerTrace.h"
#include "Templates/SharedPointer.h"
#include "InfinityFrameworkConfig.h"
#include "FrameworkCommonLibrary.h"
#include "FrameworkLuaDelegates.h"
#include "HAL/PlatformProcess.h"
#include "LuaModuleSettings.h"
#include "LuaCppInterface.h"
#include "FrameworkLua.h"
#include "HAL/Thread.h"
#include "Misc/App.h"
#include <thread>


using namespace slua;

const char* FLuaStateSubsystem::MainFunction = "Main";

const char* FLuaStateSubsystem::TickFunction = "Tick";

const char* FLuaStateSubsystem::UnmarshalExcelBinFunction = "slexcel.LoadTable";

TMap<FString,FString> FLuaStateSubsystem::OverrideLuaMap;

/* static */ const ULuaModuleSettings* FLuaStateSubsystem::ModuleSettings = nullptr;

FLuaRegisterCenter& FLuaRegisterCenter::Get()
{
	static FLuaRegisterCenter Instance;
	return Instance;
}


FLuaStateSubsystem::FLuaStateSubsystem() : bHasInit(false), bHasStart(false), State(nullptr), gameInstance(nullptr), _timerindex(0)
{
	ModuleSettings = GetDefault<ULuaModuleSettings>();
}

FLuaStateSubsystem::~FLuaStateSubsystem()
{
	ModuleSettings = nullptr;
}

FLuaStateSubsystem& FLuaStateSubsystem::GetLuaStateSubsystem()
{
	static FLuaStateSubsystem _myLuaStateMgr;
	return _myLuaStateMgr;
}

void FLuaStateSubsystem::Init(UGameInstance* Instance)
{
	CreateLuaState(Instance);
}

void FLuaStateSubsystem::Close()
{
	if (OnLuaStateSubsystemDestroyed.IsBound() == true)
	{
		OnLuaStateSubsystemDestroyed.Broadcast(State);
	}
	CloseLuaState();
	gameInstance = nullptr;
	
	//State.Reset();
    
    bHasInit = false;
    bHasStart = false;

    /*for(auto& luaStateInfoMap : LuaStates)
    {
    	luaStateInfoMap.Value.State->close();
    	luaStateInfoMap.Value.State.Reset();

    	luaStateInfoMap.Value.bHasInit = false;
    	luaStateInfoMap.Value.bHasStart = false;
    }*/

    //NS_SLUA::LuaBase::PreScriptByteCodeOverride.Unbind();

    RevertScriptByteCode();

    OverrideLuaMap.Empty();
}

void FLuaStateSubsystem::PreScriptByteCodeOverride(UFunction* BPFunc)
{
	if (IsValid(BPFunc))
	{
		OriginBPScriptCodes.Add(TWeakObjectPtr<UFunction>(BPFunc), BPFunc->Script);
	}
}


void FLuaStateSubsystem::RevertScriptByteCode()
{
	for (auto& TempFunc : OriginBPScriptCodes)
	{
		if (TempFunc.Key.IsValid())
		{
			UFunction* BPFunc = TempFunc.Key.Get();
			BPFunc->Script = TempFunc.Value;
		}
	}
}

TArray<uint8> FLuaStateSubsystem::LoadLuaFile(const char* InFn, FString& OutFilePath)
{
	if (PostLoadLuaFile.IsBound() == true)
	{
		PostLoadLuaFile.Broadcast(InFn, OutFilePath);
	}
	// 文件名, 即LuaFilePath
	FString Filename = UTF8_TO_TCHAR(InFn);
	// 获取LuaFilePath前缀, 并根据前缀区分传入路径来源
	const auto& FirstMask = Filename[0];
	FString Path;
	// 项目内的Lua脚本(不带有标识前缀)
	if (FirstMask != InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskChar)
	{
		if (ModuleSettings == nullptr)
		{
			UE_LOG(LogFrameworkLua, Error, TEXT("Lua配置对象为null"));
		}
		else
		{
			Path = FPaths::ProjectContentDir() /= ModuleSettings->LuaInGameFilePath;
		}
	}
#if WITH_EDITOR
	// 自定义Lua脚本的路径
	// Developer文件路径(带有@标识前缀)
	else if (FirstMask == InfinityFrameworkConfig::DevelopersFilePathMarkChar)
	{
		// 移除'@'标识
		Filename.RemoveAt(0);
		// 设置父路径为Developer文件路径
		Path = FPaths::GameDevelopersDir() /= Filename;
	}
#endif
	// GameFeature/Plugin(带有$标识前缀)
	else if (FirstMask == InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskChar)
	{
		// 移除'$'标识
		Filename.RemoveAt(0);
		// 设置父路径为插件路径
		Path = FPaths::ProjectPluginsDir();
	}
	// 路径拼接
	Path /= Filename.Replace(TEXT("."), TEXT("/"));
		
	TArray<uint8> Content;
	// 遍历拼接 .lua & .luac 后缀
	TArray<FString> LuaExts = {UTF8_TO_TCHAR(".lua"), UTF8_TO_TCHAR(".luac")};
	for (auto& It : LuaExts)
	{
		auto FullPath = Path + *It;

		// 将文件内容加载到content中
		FFileHelper::LoadFileToArray(Content, *FullPath);
		if (Content.Num() > 0)
		{
			OutFilePath = FullPath;
			return MoveTemp(Content);
		}
	}

	return MoveTemp(Content);
}

int32 FLuaStateSubsystem::OutputBeginDynamicEvent(slua::lua_State* L)
{
#if CPUPROFILERTRACE_ENABLED
	const char* EventName = luaL_optstring(L, 1, "None");

	FCpuProfilerTrace::OutputBeginDynamicEvent(*FString::Printf(TEXT("Lua: %s"), UTF8_TO_TCHAR(EventName)));
#endif
	return 0;
}

int32 FLuaStateSubsystem::OutputEndEvent(slua::lua_State* L)
{
#if CPUPROFILERTRACE_ENABLED
	FCpuProfilerTrace::OutputEndEvent();
#endif
	return 0;
}

int32 FLuaStateSubsystem::BuildConfigTableNewIndex(slua::lua_State* L)
{
	return 0;
}

static uint8* ReadFileEx(IPlatformFile& PlatformFile, const FString Path, uint32& Len)
{
	auto FileHandle = PlatformFile.OpenRead(*Path);

	if (FileHandle)
	{
		Len = static_cast<uint32>(FileHandle->Size());

		auto* Buf = new uint8[Len];

		FileHandle->Read(Buf, Len);

		delete FileHandle;

		return Buf;
	}

	return nullptr;
}

TArray<uint8> LoadServerFile (const char* Fn, FString& FilePath)
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	auto Path = FPaths::ProjectContentDir();

	Path += "/Lua/";

	Path += UTF8_TO_TCHAR(Fn);

	static TArray<FString> LuaExtensions = {UTF8_TO_TCHAR(".lua"),UTF8_TO_TCHAR(".luac")};
	for (auto Elem = LuaExtensions.CreateConstIterator(); Elem; ++Elem)
	{
		const auto FullPath = Path + *Elem;
		uint32 Len = 0;
		const auto buf = ReadFileEx(PlatformFile, FullPath, Len);

		if (buf != nullptr)
		{
			FilePath = FullPath;
			TArray<uint8> Buf;
			Buf.SetNumUninitialized(Len + 1); // 初始化数组大小
			FMemory::Memcpy(Buf.GetData(),buf,Len+1);
			return Buf;
		}
	}
	UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::LoadServerFile Failed: [%s]"),*Path);
	return TArray<uint8>();
}

TArray<uint8> LoadClientFile (const char* Fn, FString& FilePath)
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	auto Path = FPaths::ProjectContentDir();

	Path += "/Lua/";

	Path += UTF8_TO_TCHAR(Fn);

	FString FileContent ;

	uint32 Len = 0;
	if (FLuaStateSubsystem::GetOverrideLua(Fn,FileContent))
	{
		auto Str = std::string((char*)TCHAR_TO_ANSI(*FileContent));
		Len = Str.length();
		// UE_LOG(FrameworkLua,Log,TEXT("std:string:%s"),Str.c_str());
		//auto* Buf = new uint8[Len+1];
		TArray<uint8> Buf;
		Buf.SetNumUninitialized(Len + 1); // 初始化数组大小
		FilePath = Fn;
		
		FMemory::Memcpy(Buf.GetData(),(uint8*)Str.c_str(),Len+1);
		return Buf;
	}


	static TArray<FString> LuaExtensions = {UTF8_TO_TCHAR(".client.lua"),UTF8_TO_TCHAR(".lua"),UTF8_TO_TCHAR(".luac")};

	for (auto Elem = LuaExtensions.CreateConstIterator(); Elem; ++Elem)
	{
		const auto FullPath = Path + *Elem;

		const auto buf = ReadFileEx(PlatformFile, FullPath, Len);

		if (buf != nullptr)
		{
			FilePath = FullPath;

			TArray<uint8> Buf;
			Buf.SetNumUninitialized(Len + 1); // 初始化数组大小
			FMemory::Memcpy(Buf.GetData(),buf,Len+1);
			return Buf;
		}
	}
	UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::LoadClientFile Failed: [%s]"),*Path);
	
	return TArray<uint8>();
}

// static int32 LuaIsValidEx(lua_State* LuaState)
// {
// 	UObject* Object = (UObject*)lua_touserdata(LuaState, 1);
// 	lua_pushboolean(LuaState, IsValid(Object));
// 	return 1;
// }


void FLuaStateSubsystem::CreateLuaState(UGameInstance* Instance)
{
	gameInstance = Instance;
	
	NS_SLUA::LuaState::onInitEvent.AddRaw(this, &FLuaStateSubsystem::LuaStateInitCallback);
	
	CloseLuaState();
	State = new NS_SLUA::LuaState("FrameworkLuaState", gameInstance);
	State->setLoadFileDelegate(LoadLuaFile);
	State->init();
	LuaCppInterface::OpenLib(State->getLuaState());
	RegisterGlobalMethod();
	RegisterGlobalVariable();
	RegisterExtensionMethod();
	bHasInit = true;
	bHasStart = false;

	if (OnLuaStateSubsystemCreated.IsBound() == true)
	{
		OnLuaStateSubsystemCreated.Broadcast();
	}

	StartMainLuaState();
}

void FLuaStateSubsystem::CloseLuaState()
{
	if (State)
	{
		State->close();
		delete State;
		State = nullptr;
	}

}

static int32 PrintLogEx(NS_SLUA::lua_State* L)
{
	FString str;
	size_t len;
	const char* s = luaL_tolstring(L, 1, &len);
	if (s) str += UTF8_TO_TCHAR(s);
	NS_SLUA::Log::Log("PrintLog %s", TCHAR_TO_UTF8(*str));
	return 0;
	
}

void FLuaStateSubsystem::LuaStateInitCallback(NS_SLUA::lua_State* L)
{
	lua_pushcfunction(L, PrintLogEx);
	lua_setglobal(L, "PrintLog");

	//lua_pushcfunction(L, LuaIsValidEx);
	//lua_setglobal(L, "IsValid");
}

void FLuaStateSubsystem::Start()
{
	if (!bHasInit)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::Start => Lua has not been init!"));
		return;
	}

	if (bHasStart)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::Start => Lua already has been started!"));
		return;
	}


	UE_LOG(LogFrameworkLua, Warning, TEXT("Lua虚拟机开始运行"));
	// 载入框架文件
	State->doFile(TCHAR_TO_ANSI(*ModuleSettings->LuaFrameworkMain));
	
#if WITH_EDITOR
	// 如果是编辑器模式，可以连接 IED 的 Debug Server
	// 通过Lua状态机调用_G.StartLuaPanda函数
	State->call(TCHAR_TO_ANSI(*ModuleSettings->LuaPandaStarterFuncName), ModuleSettings->IP, ModuleSettings->Port);
#endif
	
	// 通过Lua状态机调用_G.Main函数
	State->call(MainFunction,gameInstance);
	bHasStart = true;
	// 通过Lua状态机设置TickFunction
	State->setTickFunction(GetVar(TickFunction));
}

void FLuaStateSubsystem::EmptyPool()
{
	if (HasReady())
	{
		//State->EmptyLuaDelegatePool();
	}
	else
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::EmptyPool => Lua has not been ready!"));
	}
}

LuaVar FLuaStateSubsystem::GetVar(const char* Key) const
{
	if (!HasReady())
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::GetVar => Lua has not been ready!"));
		return slua::LuaVar();
	}

	return State->get(Key);
}

bool FLuaStateSubsystem::SetVar(const char* Key, const slua::LuaVar& Value) const
{
	if (!HasReady())
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::SetVar => Lua has not been ready!"));

		return false;
	}

	return State->set(Key, Value);
}

void FLuaStateSubsystem::DoString(const char* Str) const
{
	if (!HasReady())
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::DoString => Lua has not been ready!"));

		return;
	}

	State->doString(Str);
}

void FLuaStateSubsystem::RegisterGlobalMethod()
{
	using namespace slua;

	const auto L = State->getLuaState();

	if (L == nullptr)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::RegisterGlobalMethod => L is nullptr!"));
		return;
	}

	FLuaRegisterCenter::Get().RegisterGlobalMethods(L);

	lua_register(L, "OutputBeginDynamicEvent", &FLuaStateSubsystem::OutputBeginDynamicEvent);
	lua_register(L, "OutputEndEvent", &FLuaStateSubsystem::OutputEndEvent);
}

void FLuaStateSubsystem::RegisterGlobalVariable()
{
	slua::lua_State* L = State ? State->getLuaState() : nullptr;
	if (!L)
	{
		return;
	}

	lua_newtable(L); // readonly build config table
	lua_newtable(L); // metatable
	lua_newtable(L); // configs

	lua_pushboolean(L, !!CPUPROFILERTRACE_ENABLED);
	lua_setfield(L, -2, "CPUPROFILERTRACE_ENABLED");
	lua_pushboolean(L, !!STATS);
	lua_setfield(L, -2, "STATS");
	lua_pushboolean(L, !!UE_BUILD_DEBUG);
	lua_setfield(L, -2, "UE_BUILD_DEBUG");
	lua_pushboolean(L, !!UE_BUILD_DEVELOPMENT);
	lua_setfield(L, -2, "UE_BUILD_DEVELOPMENT");
	lua_pushboolean(L, !!UE_BUILD_TEST);
	lua_setfield(L, -2, "UE_BUILD_TEST");
	lua_pushboolean(L, !!UE_BUILD_SHIPPING);
	lua_setfield(L, -2, "UE_BUILD_SHIPPING");
	lua_pushboolean(L, !!UE_SERVER);
	lua_setfield(L, -2, "UE_SERVER");

	lua_setfield(L, -2, "__index"); // metatable.__index = configs
	lua_pushcfunction(L, &FLuaStateSubsystem::BuildConfigTableNewIndex);
	lua_setfield(L, -2, "__newindex"); // metatable.__newindex = LuaSubsystem::BuildConfigTableNewIndex
	
	lua_setmetatable(L, -2);

	lua_setglobal(L, "BuildConfig");

	const int32 StackCount = lua_gettop(L);
	if (StackCount != 0)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("Lua state stack count is non-zero: %d, after LuaSubsystem::RegisterGlobalVariable!"), StackCount);
	}
}

void FLuaStateSubsystem::RegisterExtensionMethod()
{
	using namespace slua;

	REG_EXTENSION_METHOD_IMP(
		UObject,
		"IsA",
		{
		CheckUD(UObject, L, 1);

		UClass* Class = LuaObject::checkValueOpt<UClass*>(L, 2, nullptr);

		return LuaObject::push(L, UD->IsA(Class));
		}
	);

	FLuaRegisterCenter::Get().RegisterExtensionMethods();
}

void FLuaStateSubsystem::StartMainLuaState()
{
	Start();
	if (OnLuaStateSubsystemStarted.IsBound() == true)
	{
		OnLuaStateSubsystemStarted.Broadcast(State, gameInstance);
	}
}

void FLuaStateSubsystem::StartHotFixLuaState()
{
	StartLuaState("HotFixLuaState");
}

void FLuaStateSubsystem::StopHotFixLuaState()
{
	StopLuaState("HotFixLuaState");
}

void FLuaStateSubsystem::StartHotPatchLuaState()
{
	StartLuaState("HotPatchLuaState");
}

void FLuaStateSubsystem::StopHotPatchLuaState()
{
	StopLuaState("HotPatchLuaState");
}


void FLuaStateSubsystem::NewLuaState(const char* LuaStateName,const char*  MainF,const char*  MainFunc, const 
								char*  TickFunc)
{
	TSharedPtr<NS_SLUA::LuaState> LuaState = MakeShared<NS_SLUA::LuaState>(LuaStateName,gameInstance);

	/*LuaState->SetbIsStateTickable(false);

	if (UKismetSystemLibrary::IsDedicatedServer(this))
	{
		LuaState->setLoadFileDelegate(LoadServerFile);
	}
	else
	{
		LuaState->setLoadFileDelegate(LoadClientFile);
	}*/
	
	LuaStates.Add(LuaStateName ,{LuaState,LuaStateName,MainF,MainFunc,TickFunc,LuaState->init(),false});
	
	RegisterGlobalMethod(LuaState);
	
	RegisterGlobalVariable(LuaState);
	
	UE_LOG(LogFrameworkLua, Log, TEXT("LuaSubsystem::NewLuaState => Lua State %hs added to map!"), LuaStateName);

}

void FLuaStateSubsystem::StartLuaState(const char* LuaStateName)
{
	const FString LsName = FString(LuaStateName);
	
	if ( LuaStates.Contains(LsName))
	{
		FLuaStateInfo& LuaStateInfo = LuaStates[LsName];
		if (!LuaStateInfo.bHasInit)
		{
			UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState => Lua State %s has not been init!"),*LsName);
			return;
		}

		if (LuaStateInfo.bHasStart)
		{
			UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState =>  Lua State %s already has been started!"),*LsName);
			return;
		}
		
		LuaStateInfo.State->doFile(TCHAR_TO_ANSI(*LuaStateInfo.MainFile));

		LuaStateInfo.State->call(TCHAR_TO_ANSI(*LuaStateInfo.MainFunction), gameInstance);

		LuaStateInfo.bHasStart = true;
		
		LuaStateInfo.State->setTickFunction(GetVar(LuaStateName,TCHAR_TO_ANSI(*LuaStateInfo.TickFunction)));
		
		UE_LOG(LogFrameworkLua, Log, TEXT("LuaSubsystem::StartLuaState => Lua State %s Started!"),*LsName);
	}else{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState => Lua State %s Not Found!"),*LsName);
	}
	
	
}

void FLuaStateSubsystem::StopLuaState(const char* LuaStateName)
{
	const FString LsName = FString(LuaStateName);
	
	if ( LuaStates.Contains(LsName))
	{
		FLuaStateInfo& LuaStateInfo = LuaStates[LsName];
		if (!LuaStateInfo.bHasInit)
		{
			UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState => Lua State %s has not been init!"),*LsName);
			return;
		}

		if (!LuaStateInfo.bHasStart)
		{
			UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState =>  Lua State %s already has Not started!"),*LsName);
			return;
		}
		
		LuaStateInfo.State->setTickFunction( slua::LuaVar());
		//LuaStateInfo.State->SetbIsStateTickable(false);
		//LuaStateInfo.State->EmptyLuaDelegatePool();
	
		gameInstance->GetWorld()->GetTimerManager().SetTimerForNextTick(
			FTimerDelegate::CreateLambda([LuaStateInfo,LsName]()
			{
				LuaStateInfo.State->close();
				UE_LOG(LogFrameworkLua, Log, TEXT("LuaSubsystem::StartLuaState =>  Lua State %s Stopped!"),*LsName);
			}));
		
	}else{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::StartLuaState => Lua State %s Not Found!"),*LsName);
	}
}

slua::LuaVar FLuaStateSubsystem::GetVar(const char* LuaStateName, const char* Key)
{
	const FString LsName= FString(LuaStateName);
	if ( LuaStates.Contains(LsName))
	{
		if (!(LuaStates[LsName].bHasInit && LuaStates[LsName].bHasStart))
		{
			UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::GetVar => Lua has not been ready!"));
			return slua::LuaVar();
		}

		return 	LuaStates[LsName].State->get(Key);
	}
	return slua::LuaVar();
}

void FLuaStateSubsystem::OverrideLua(const FString& Key, const FString& Code)
{
	OverrideLuaMap.Add(Key,Code);
}

bool FLuaStateSubsystem::GetOverrideLua(const FString& Key, FString& OutFileContent)
{
	if (OverrideLuaMap.Contains(Key))
	{
		OutFileContent = OverrideLuaMap[Key];
		return true;
	}
	
	return false;
}

void FLuaStateSubsystem::RegisterGlobalMethod(TSharedPtr<NS_SLUA::LuaState> S)
{
	using namespace slua;

	const auto L = S->getLuaState();

	if (L == nullptr)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("LuaSubsystem::RegisterGlobalMethod => L is nullptr!"));
		return;
	}

	FLuaRegisterCenter::Get().RegisterGlobalMethods(L);
	//VFLuaStats::LuaStatsRegister(L);

	lua_register(L, "OutputBeginDynamicEvent", &FLuaStateSubsystem::OutputBeginDynamicEvent);
	lua_register(L, "OutputEndEvent", &FLuaStateSubsystem::OutputEndEvent);
}

void FLuaStateSubsystem::RegisterGlobalVariable(TSharedPtr<NS_SLUA::LuaState> S)
{
	slua::lua_State* L = S.IsValid() ? S->getLuaState() : nullptr;
	if (!L)
	{
		return;
	}

	lua_newtable(L); // readonly build config table
	lua_newtable(L); // metatable
	lua_newtable(L); // configs

	lua_pushboolean(L, !!CPUPROFILERTRACE_ENABLED);
	lua_setfield(L, -2, "CPUPROFILERTRACE_ENABLED");
	lua_pushboolean(L, !!STATS);
	lua_setfield(L, -2, "STATS");
	lua_pushboolean(L, !!UE_BUILD_DEBUG);
	lua_setfield(L, -2, "UE_BUILD_DEBUG");
	lua_pushboolean(L, !!UE_BUILD_DEVELOPMENT);
	lua_setfield(L, -2, "UE_BUILD_DEVELOPMENT");
	lua_pushboolean(L, !!UE_BUILD_TEST);
	lua_setfield(L, -2, "UE_BUILD_TEST");
	lua_pushboolean(L, !!UE_BUILD_SHIPPING);
	lua_setfield(L, -2, "UE_BUILD_SHIPPING");
	lua_pushboolean(L, !!UE_SERVER);
	lua_setfield(L, -2, "UE_SERVER");

	lua_setfield(L, -2, "__index"); // metatable.__index = configs
	lua_pushcfunction(L, &FLuaStateSubsystem::BuildConfigTableNewIndex);
	lua_setfield(L, -2, "__newindex"); // metatable.__newindex = LuaSubsystem::BuildConfigTableNewIndex
	
	lua_setmetatable(L, -2);

	lua_setglobal(L, "BuildConfig");

	const int32 StackCount = lua_gettop(L);
	if (StackCount != 0)
	{
		UE_LOG(LogFrameworkLua, Warning, TEXT("Lua state stack count is non-zero: %d, after LuaSubsystem::RegisterGlobalVariable!"), StackCount);
	}
}


int FLuaStateSubsystem::SetTimer(float interval, bool looping, void * func)
{
	slua::LuaVar *f = (slua::LuaVar*) func;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([](slua::LuaVar*func) {if (func) func->call(); }, f);
	FTimerHandle handler;
	gameInstance->GetTimerManager().SetTimer(handler, timerDelegate, interval, looping);
	++_timerindex;
	_timers.Add(_timerindex, handler);
	return _timerindex;
}

int FLuaStateSubsystem::ClearTimer(int idx)
{
	if (!_timers.Contains(idx))
		return 0;

	FTimerHandle handler = _timers[idx];
	_timers.Remove(idx);
	gameInstance->GetTimerManager().ClearTimer(handler);
	return 0;
}

int FLuaStateSubsystem::ClearAllTimers()
{
	for (TPair<int, FTimerHandle> it : _timers)
	{
		gameInstance->GetTimerManager().ClearTimer(it.Value);
	}
	_timers.Empty();
	_timerindex = 0;
	return 0;
}