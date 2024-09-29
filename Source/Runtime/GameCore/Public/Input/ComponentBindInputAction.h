#pragma once

#include "ComponentBindInputAction.generated.h"

enum class ETriggerEvent : uint8;

/**
 * @brief 对于组件需要绑定的InputAction的封装
 */
USTRUCT(BlueprintType)
struct FComponentBindInputAction
{
	GENERATED_BODY()

	/**
	 * @brief 需要绑定的TriggerEvents
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TArray<ETriggerEvent> NeedBindTriggerEvents;
	/**
	 * @brief 需要绑定的InputAction
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FSoftObjectPath InputActionObjectPath = nullptr;
};

/**
 * @brief 组件绑定输入所需数据
 */
USTRUCT(BlueprintType)
struct FComponentBindInputData
{
	GENERATED_BODY()

	/**
	 * @brief 需要绑定的Component
	 * @note 一般情况下应该为this
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UActorComponent* Component = nullptr;
	/**
	 * @brief 需要绑定的InputActions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TArray<FComponentBindInputAction> BindInputActions;
};