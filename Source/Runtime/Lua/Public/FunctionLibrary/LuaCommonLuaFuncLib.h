// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace slua
{
	template<typename T>
	struct LuaOwnedPtr;
	struct Lua_State;
}

using namespace slua;
/**
 * @brief 通过绑定直接提供给Lua访问的通用行为函数库
 */
class FRAMEWORKLUA_API FLuaCommonLuaFuncLib
{
public:
	/**
	 * @brief 获取插件的Lua文件路径
	 * @note 主要提供跨插件调用，以及插件内部调用
	 * @param InGameFeatureName 插件名
	 * @param InFilePath 文件路径
	 * @return 用于加载的luaFile路径
	 */
	static FString FileInPlugin(const FString& InGameFeatureName, const FString& InFilePath);
	/**
	 * @brief 获取GameFeature的Lua文件路径
	 * @note 主要提供跨插件调用，以及插件内部调用
	 * @param InGameFeatureName GameFeature名
	 * @param InFilePath 文件路径
	 * @return 用于加载的luaFile路径
	 */
	static FString FileInGameFeature(const FString& InGameFeatureName, const FString& InFilePath);

	/**
	 * @private 在lua中访问的创建函数
	 * @return FLuaCommonLuaFuncLib对象
	 */
	static LuaOwnedPtr<FLuaCommonLuaFuncLib> Create();
};
