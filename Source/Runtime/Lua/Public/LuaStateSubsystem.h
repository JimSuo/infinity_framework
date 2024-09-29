/**
 * @copyright Infinity Framework
 * 
 * @brief   包含Lua状态机相关拓展逻辑
 * 
 * 包括拓展Lua状态机相关的功能
 * 
 * @date    2024-07-03
 * 
 * @author  WangXianWei
 * @contact http://172.16.0.13:8099/root
 */

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"

class ULuaModuleSettings;

/**
 * @brief Lua状态机信息
 */
struct FLuaStateInfo
{
	TSharedPtr<NS_SLUA::LuaState> State;
	FString Name;
	FString MainFile;
	FString MainFunction;
	FString TickFunction;
	bool bHasInit;
	bool bHasStart;
};

/**
 * @brief 处理所有Lua注册逻辑
 */
struct FRAMEWORKLUA_API FLuaRegisterCenter
{
	static FLuaRegisterCenter& Get();


	void AddGlobalMethods(TFunction<void(slua::lua_State* L)> Entry)
	{
		GlobalMethodEntries.Add(Entry);
	}

	void AddExtensionMethods(TFunction<void()> Entry)
	{
		ExtensionlMethodEntries.Add(Entry);
	}

	void RegisterGlobalMethods(slua::lua_State* L) const
	{
		for (auto& Entry : GlobalMethodEntries)
		{
			Entry(L);
		}
	}

	void RegisterExtensionMethods() const
	{
		for (auto& Entry : ExtensionlMethodEntries)
		{
			Entry();
		}
	}

private:
	TArray<TFunction<void(slua::lua_State* L)>> GlobalMethodEntries;
	TArray<TFunction<void()>> ExtensionlMethodEntries;
};


struct FLuaRegisterEntry
{
	FLuaRegisterEntry(TFunction<void(slua::lua_State* L)> Entry)
	{
		FLuaRegisterCenter::Get().AddGlobalMethods(Entry);
	}

	FLuaRegisterEntry(TFunction<void()> Entry)
	{
		FLuaRegisterCenter::Get().AddExtensionMethods(Entry);
	}
};

/**
 * @brief Lua状态机子系统
 * @note 此处以Subsystem结尾命名不代表这个类型是一个Subsystem类型的子类, 是为了表现其层级以及命名统一才使用Subsystem作为结尾
 */
class FRAMEWORKLUA_API FLuaStateSubsystem
{

public:
	
	~FLuaStateSubsystem();

	/**
	 * @brief 获取Lua状态机子系统
	 */
	static FLuaStateSubsystem & GetLuaStateSubsystem();
	
	void Init(UGameInstance* Instance);
	void Close();

	void CreateLuaState(UGameInstance* Instance);
	void CloseLuaState();
	void LuaStateInitCallback(NS_SLUA::lua_State* L);
	
	void Start();

	void EmptyPool();

	slua::LuaVar GetVar(const char* Key) const;

	bool SetVar(const char* Key, const slua::LuaVar& Value) const;

	void DoString(const char* Str) const;

	template <typename ...ARGS>
	slua::LuaVar Call(const char* Key, ARGS&& ...Args)
	{
		if (!HasReady())
		{
			UE_LOG(LogTemp, Error, TEXT("UVFLuaSubsystem::Call => State is not ready"));

			return slua::LuaVar();
		}
		else
		{
			return State->call(Key, Args...);
		}
	}

	void PreScriptByteCodeOverride(UFunction* BPFunc);
	
	int SetTimer(float invterval, bool looping, void * func);
	int ClearTimer(int idx);
	int ClearAllTimers();

protected:
	// 模块配置
	static const ULuaModuleSettings* ModuleSettings;

	
	void RevertScriptByteCode();

	/**
	 * @brief 加载Lua文件
	 * @param InFn Lua对象的LuaFilePath 
	 * @param OutFilePath Lua脚本的绝对路径 
	 * @return LuaContent 
	 */
	static TArray<uint8> LoadLuaFile(const char* InFn, FString& OutFilePath);

	/**
	 * 输出开始动态事件
	 * @param L Lua状态机
	 * @return 输出结果
	 */
	static int32 OutputBeginDynamicEvent(slua::lua_State* L);
	static int32 OutputEndEvent(slua::lua_State* L);
	static int32 BuildConfigTableNewIndex(slua::lua_State* L);

private:

	FLuaStateSubsystem();
	
	bool bHasInit;

	bool bHasStart;
	
	NS_SLUA::LuaState* State;
	UGameInstance* gameInstance;

	TMap<int, FTimerHandle> _timers;
	int _timerindex;
	
	static const char* MainFunction;

	static const char* TickFunction;

	static const char* UnmarshalExcelBinFunction;

	void RegisterGlobalMethod();
	void RegisterGlobalVariable();

	static void RegisterExtensionMethod();

	TMap<TWeakObjectPtr<UFunction>, TArray<uint8>> OriginBPScriptCodes;


#if PLATFORM_LINUX
	bool bLinuxPlatformDSFork = false;
	void LinuxPlatformDSFork() const;
#endif

	

private:
	void RegisterGlobalMethod(TSharedPtr<NS_SLUA::LuaState> S);
	void RegisterGlobalVariable(TSharedPtr<NS_SLUA::LuaState> S);

	static TMap<FString,FString> OverrideLuaMap;
public:
	FORCEINLINE bool HasReady() const
	{
		return bHasInit && bHasStart;
	}
	
	TMap<FString,FLuaStateInfo> LuaStates;

	void StartMainLuaState();
	
	void StartHotFixLuaState();

	void StopHotFixLuaState();

	void StartHotPatchLuaState();

	void StopHotPatchLuaState();
	
	void NewLuaState(const char* LuaStateName,const char*  MainF,const char*  MainFunc, const char*  
	TickFunc);
	
	void StartLuaState(const char* LuaStateName);

	void StopLuaState(const char* LuaStateName);
	
	slua::LuaVar GetVar(const char* LuaStateName,const char* Key);

	static void OverrideLua(const FString& Key, const FString& Code);

	static bool GetOverrideLua(const FString& Key, FString& OutFileContent);

};
