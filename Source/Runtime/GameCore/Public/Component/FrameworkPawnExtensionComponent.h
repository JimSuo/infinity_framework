// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"

#include "FrameworkPawnComponent.h"

#include "FrameworkPawnExtensionComponent.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
class UInputComponent;
class APawn;

/**
 * @brief 框架的Pawn拓展插件
 * @note 支持Pawn的能力拓展(EnhanceInput，GAS，GameFeature等)，Lua能力
 */
UCLASS(ClassGroup=(Custom), Category="Framework|Component", meta=(BlueprintSpawnableComponent))
class FRAMEWORKGAMECORE_API UFrameworkPawnExtensionComponent : public UFrameworkPawnComponent
{
	GENERATED_BODY()

public:
	UFrameworkPawnExtensionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * @brief 在Actor上查找Pawn的拓展组件
	 * @param InPawn 组件所在的Pawn对象
	 */
	UFUNCTION(BlueprintPure, Category = "Framework|Pawn")
	static UFrameworkPawnExtensionComponent* FindPawnExtensionComponent(const APawn* InPawn);

	/**
	 * @brief 设置玩家输入
	 * @param InPawn 组件所在的Pawn对象
	 * @param InInputComponent 输入组件
	 */
	static void SetupPlayerInputComponent(const APawn* InPawn, UInputComponent* InInputComponent);
	
protected:
	void SetupPlayerInputComponent(UEnhancedInputComponent* InEnhancedInputComponent) const;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;
};
