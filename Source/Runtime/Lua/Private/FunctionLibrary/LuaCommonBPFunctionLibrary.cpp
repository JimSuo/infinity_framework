// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCommonBPFunctionLibrary.h"

#include "FrameworkCommonLibrary.h"
#include "FrameworkLua.h"
#include "LuaFilePathConstruceMacro.h"

bool ULuaCommonBPFunctionLibrary::WithInEditor()
{
	return FFrameworkCommonLibrary::WithInEditor();
}

FString ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath(const FName& InPluginName, const FString& InLuaFilePath)
{
	if (InPluginName.ToString().IsEmpty())
	{
		UE_LOG(LogFrameworkLua, Error, TEXT("[ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath] : Plugin name is empty!!!"));
		return TEXT("");
	}
	if (InLuaFilePath.IsEmpty())
	{
		UE_LOG(LogFrameworkLua, Error, TEXT("[ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath] : Lua file path is empty!!!"));
		return TEXT("");
	}
	_MAKE_PLUGIN_LUA_FILE_PATH(NewPath, InPluginName, InLuaFilePath)
	return NewPath;
}

FString ULuaCommonBPFunctionLibrary::ConstructGameFeatureLuaFilePath(const FName& InGameFeatureFileName,
                                                                     const FString& InLuaFilePath)
{
	if (InGameFeatureFileName.ToString().IsEmpty())
	{
		UE_LOG(LogFrameworkLua, Error, TEXT("[ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath] : Gamefeature name is empty!!!"));
		return TEXT("");
	}
	if (InLuaFilePath.IsEmpty())
	{
		UE_LOG(LogFrameworkLua, Error, TEXT("[ULuaCommonBPFunctionLibrary::ConstructPluginLuaFilePath] : Lua file path is empty!!!"));
		return TEXT("");
	}
	_MAKE_GAME_FEATURE_LUA_FILE_PATH(NewPath, InGameFeatureFileName, InLuaFilePath)
	return NewPath;
}

FString ULuaCommonBPFunctionLibrary::GetGameContentDir()
{
	return FPaths::GetPath(FPaths::ProjectContentDir());
}
