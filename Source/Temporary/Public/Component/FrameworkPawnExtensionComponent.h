// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"

#include "FrameworkPawnComponent.h"

#include "FrameworkPawnExtensionComponent.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;

/**
 * @brief 框架的Pawn拓展插件
 * @note 支持Pawn的能力拓展(GAS，GameFeature等)，Lua能力
 */
UCLASS(ClassGroup=(Custom), Category="Framework|Component", meta=(BlueprintSpawnableComponent))
class FRAMEWORKTEMPORARY_API UFrameworkPawnExtensionComponent : public UFrameworkPawnComponent
{
	GENERATED_BODY()

public:
	UFrameworkPawnExtensionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * @brief 在Actor上查找Pawn的拓展组件
	 * @param InActor 组件所在的对象
	 */
	UFUNCTION(BlueprintPure, Category = "Framework|Pawn")
	static UFrameworkPawnExtensionComponent* FindPawnExtensionComponent(const AActor* InActor);

	/**
	 * @brief 设置玩家输入
	 * @param InEnhancedInputComponent 增强输入组件
	 */
	void SetupPlayerInputComponent(UEnhancedInputComponent* InEnhancedInputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMapping;
};
