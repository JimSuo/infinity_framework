// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFeatureOverrideInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameFeatureOverrideInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FRAMEWORKGAMEFEATURE_API IGameFeatureOverrideInterface
{
	GENERATED_BODY()

public:
	// 获取GameFeature名
	UFUNCTION(BlueprintNativeEvent)
	FString GetGameFeatureName() const;
};
