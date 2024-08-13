// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LuaOverriderInterface.h"
#include "LuaCommonActivatableWidget.generated.h"

/**
 * @brief 框架的CommonActivatableWidget对象
 * @note 具有sLua能力
 */
UCLASS()
class FRAMEWORKLUA_API ULuaCommonActivatableWidget : public UCommonActivatableWidget, public ILuaOverriderInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;

	virtual bool Initialize() override;
	virtual void BeginDestroy() override;

	virtual FString GetLuaFilePath_Implementation() const override;
};
