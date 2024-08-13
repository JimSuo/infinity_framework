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
};
