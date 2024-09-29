// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureOverrideInterface.h"
#include "LuaActorComponent.h"

#include "GameFeatureActorComponent.generated.h"

/**
 * @brief 只在GameFeature中使用的ActorComponent
 */
UCLASS(ClassGroup=(Framework), meta=(BlueprintSpawnableComponent))
class FRAMEWORKGAMEFEATURE_API UGameFeatureActorComponent : public ULuaActorComponent, public IGameFeatureOverrideInterface
{
	GENERATED_BODY()
	
public:
	UGameFeatureActorComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Framework Game Feature Interface Begin
	virtual FString GetGameFeatureName_Implementation() const override;
	//~ Framework Game Feature Interface End
	
	//~ sLua Interface Begin
	virtual FString GetLuaFilePath_Implementation() const override;
	//~ sLua Interface End

private:
	//~ GameFeature Property Begin
	/**
	 * @brief GameFeature名
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameFeature, meta=(AllowPrivateAccess))
	FName GameFeatureName;
	//~ GameFeature Property End
};
