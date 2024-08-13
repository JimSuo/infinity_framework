// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ListenPlayerInput.generated.h"

class UEnhancedInputComponent;
struct FInputActionInstance;
class UInputAction;

// This class does not need to be modified.
UINTERFACE()
class UListenPlayerInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brife 监听玩家输入接口
 */
class FRAMEWORKTEMPORARY_API IListenPlayerInput
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
	TArray<FSoftObjectPath> GetInputActionPaths();
	/**
	 * @brief 注册输入
	 * @note *关键函数，可在此函数中添加监听，必须重写此函数*
	 * @param InputComponent 输入组件
	 * @param InputAction 注册时输入行为
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Input")
	void InitPlayerInput(UEnhancedInputComponent* InputComponent, UInputAction* InputAction);
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
