// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InfinityFrameworkConfig.h"

#include "LuaModuleSettings.generated.h"

/**
 * 框架的Lua模块设置
 */
UCLASS(config=Framework, defaultconfig, meta=(DisplayName="Lua Module Settings"))
class FRAMEWORKLUA_API ULuaModuleSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	ULuaModuleSettings()
	{
		CategoryName = InfinityFrameworkConfig::FrameworkSettingsCategory;
	}

	/**
	 * @brief LuaFramework文件夹中的Main.Lua文件在Content的Lua文件夹下的相对路径
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config=LuaFilePath, Category=LuaFile)
	FString LuaFrameworkMain = TEXT("Main");
	/**
	 * @brief Lua文件在Game中的路径
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config=LuaFilePath, Category=LuaFile)
	FString LuaInGameFilePath = TEXT("Core/Lua");
	/**
	 * @brief Lua文件在Game中的路径
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config=LuaFilePath, Category=LuaFile)
	FString LuaPandaStarterFuncName = TEXT("StartLuaPanda");
	/**
	 * @brief 连接的IP
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config=LuaPandaConnectConfig, Category=LuaPandaConnect)
	FString IP = "127.0.0.1";
	/**
	 * @brief 连接的端口
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config=LuaPandaConnectConfig, Category=LuaPandaConnect)
	int32 Port = 8818;
};