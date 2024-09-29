#include "LuaCommonLuaFuncLib.h"
#include "LuaCommonBPFunctionLibrary.h"
#include "LuaCppBinding.h"
#include "LuaObject.h"

namespace NS_SLUA
{
	DefLuaClass(FLuaCommonLuaFuncLib)
	DefLuaMethod(FileInPlugin, &FLuaCommonLuaFuncLib::FileInPlugin)
	DefLuaMethod(FileInGameFeature, &FLuaCommonLuaFuncLib::FileInGameFeature)
	EndDef(FLuaCommonLuaFuncLib, &FLuaCommonLuaFuncLib::Create)
}

FString FLuaCommonLuaFuncLib::FileInPlugin(const FString& InGameFeatureName, const FString& InFilePath)
{
	return ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath(FName(InGameFeatureName), InFilePath);
}

FString FLuaCommonLuaFuncLib::FileInGameFeature(const FString& InGameFeatureName, const FString& InFilePath)
{
	return ULuaCommonBPFunctionLibrary::ConstructGameFeatureLuaFilePath(FName(InGameFeatureName), InFilePath);
}

LuaOwnedPtr<FLuaCommonLuaFuncLib> FLuaCommonLuaFuncLib::Create()
{
	return new FLuaCommonLuaFuncLib;
}
