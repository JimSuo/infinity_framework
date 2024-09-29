// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfinityFrameworkConfig.h"

#include "UIManagerSettings.generated.h"

class UFrameworkUIPolicy;

/**
 * UI管理器设置
 */
UCLASS(config=Framework, defaultconfig, meta=(DisplayName="UI Manager Settings"))
class FRAMEWORKGAMECORE_API UUIManagerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UUIManagerSettings()
	{
		CategoryName = InfinityFrameworkConfig::FrameworkSettingsCategory;
	}
	
	/**
	 * @brief 是否为VR项目
	 */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly)
	bool VR = false;
	/**
	 * @brief 当前UI策略在DefaultFramework.ini中的UI策略类引用配置
	 */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UFrameworkUIPolicy> DefaultUIPolicyClass;
};
