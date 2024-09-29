// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaCommonBPFunctionLibrary.generated.h"

/**
 * @brief 提供给Lua访问的通用行为蓝图函数库
 */
UCLASS()
class FRAMEWORKLUA_API ULuaCommonBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief 获取是否在编辑器启动
	 * @return 是否在编辑器启动
	 */
	UFUNCTION(BlueprintCallable, Category="Lua")
	static bool WithInEditor();

	/**
	 * @brief 构造一个基于Plugin路径下的LuaFilePath路径
	 * @param InPluginName Plugin的文件名
	 * @param InLuaFilePath 相对于 [ProjectContentDir]/Core/Lua/ 路径下的Lua文件路径
	 * @return [ProjectPluginsDir]/[InfinityFrameworkConfig::LuaFileRelativePath]/[InLuaFilePath]
	 */
	UFUNCTION(BlueprintCallable, Category="Lua")
	static FString ConstructPluginLuaFilePath(const FName& InPluginName, const FString& InLuaFilePath);
	/**
	 * @brief 构造一个基于GameFeature路径下的LuaFilePath路径
	 * @param InGameFeatureFileName GameFeature的文件名
	 * @param InLuaFilePath 相对于 Lua/ 路径下的Lua文件路径
	 * @return [ProjectPluginsDir]/GameFeatures/[InfinityFrameworkConfig::LuaFileRelativePath]/[InLuaFilePath]
	 */
	UFUNCTION(BlueprintCallable, Category="Lua")
	static FString ConstructGameFeatureLuaFilePath(const FName& InGameFeatureFileName, const FString& InLuaFilePath);

	// 获取Content路径
	UFUNCTION(BlueprintCallable)
	static FString GetGameContentDir();
};
