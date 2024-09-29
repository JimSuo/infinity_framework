// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Delegates/Delegate.h"
#include "LuaState.h"

class NS_SLUA::LuaState;
class UGameInstance;

/**
 * @brief 存储框架Lua模块相关的回调类型
 */

/**
 * @brief Lua虚拟机创建时执行
 */
DECLARE_MULTICAST_DELEGATE(OnLuaStateSubsystemCreatedEvent)
/**
 * @brief Lua虚拟机执行Start时执行
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(OnLuaStateSubsystemStartedEvent, NS_SLUA::LuaState*, UGameInstance*)
/**
 * @brief Lua虚拟机销毁时执行
 */
DECLARE_MULTICAST_DELEGATE_OneParam(OnLuaStateSubsystemDestroyedEvent, NS_SLUA::LuaState*)
/**
 * @brief Lua虚拟机读取文件时执行
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(PostLoadLuaFileEvent, const char*, FString&)


/**
 * @brief 回调事件的全局声明
 */

extern FRAMEWORKLUA_API OnLuaStateSubsystemCreatedEvent OnLuaStateSubsystemCreated;
extern FRAMEWORKLUA_API OnLuaStateSubsystemStartedEvent OnLuaStateSubsystemStarted;
extern FRAMEWORKLUA_API OnLuaStateSubsystemDestroyedEvent OnLuaStateSubsystemDestroyed;
extern FRAMEWORKLUA_API PostLoadLuaFileEvent PostLoadLuaFile;