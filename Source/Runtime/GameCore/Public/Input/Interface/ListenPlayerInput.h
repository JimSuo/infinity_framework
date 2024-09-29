// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ListenPlayerInput.generated.h"

class UEnhancedInputComponent;
class UInputAction;

struct FComponentBindInputData;
struct FInputActionInstance;

enum class ETriggerEvent : uint8;

// This class does not need to be modified.
UINTERFACE()
class UListenPlayerInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brife 监听玩家输入接口
 */
class FRAMEWORKGAMECORE_API IListenPlayerInput
{
	GENERATED_BODY()

public:
	/**
	 * @brief 注册输入
	 * @param InputComponent 输入组件
	 */
	void SetupInput(UEnhancedInputComponent* InputComponent);
	
protected:
	/**
	 * @brief 获取需要注册的输入行为对象路径数组
	 * @note *关键函数，如果想要监听输入行为，必须重写此函数*
	 * @return 需要注册的输入行为对象路径数组
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	FComponentBindInputData GetBindInputData() const;
	
	/**
	 * @brief 注册输入
	 * @note *关键函数，可在此函数中添加监听，必须重写此函数*
	 * @param InputComponent 输入组件
	 * @param InInputAction 需要进行绑定的Action数据
	 * @param InComponent 需要进行绑定的组件对象
	 * @param InTriggerEvents 需要进行绑定的出发类型数组
	 */
	void BindPlayerInput(UEnhancedInputComponent* InputComponent,
	                     UInputAction* InInputAction,
	                     UActorComponent* InComponent,
	                     const TArray<ETriggerEvent>& InTriggerEvents);
	/**
	 * @brief Trigger时执行
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void OnInputTriggeredDo(const FInputActionInstance& ActionInstance);
	/**
	 * @brief Started时执行
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void OnInputStartedDo(const FInputActionInstance& ActionInstance);
	/**
	 * @brief Ongoing时执行
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void OnInputOngoingDo(const FInputActionInstance& ActionInstance);
	/**
	 * @brief Canceled时执行
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void OnInputCanceledDo(const FInputActionInstance& ActionInstance);
	/**
	 * @brief Completed时执行
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void OnInputCompletedDo(const FInputActionInstance& ActionInstance);
};
