#include "ListenPlayerInput.h"

#include "ComponentBindInputAction.h"
#include "EnhancedInputComponent.h"
#include "InputTriggers.h"
#include "InputAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ListenPlayerInput)

// 添加组件绑定输入Log类型
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkComponentBindPlayerInput, Log, All);
DEFINE_LOG_CATEGORY(LogFrameworkComponentBindPlayerInput);

void IListenPlayerInput::SetupInput(UEnhancedInputComponent* InputComponent)
{
	const auto& BindInputData = GetBindInputData_Implementation();
	const auto& BindInputActions = BindInputData.BindInputActions;
	// 遍历配置输入路径
	for (const auto& BindAction : BindInputActions)
	{
		auto* InputAction = Cast<UInputAction>(BindAction.InputActionObjectPath.TryLoad());
		if (InputAction == nullptr)
		{
			UE_LOG(LogFrameworkComponentBindPlayerInput, Error, TEXT("软引用路径配置错误，请确引用对象为InputAction"));
			continue;
		}
		BindPlayerInput(InputComponent, InputAction, BindInputData.Component, BindAction.NeedBindTriggerEvents);
	}
}

void IListenPlayerInput::BindPlayerInput(UEnhancedInputComponent* InputComponent,
                                         UInputAction* InInputAction,
                                         UActorComponent* InComponent,
                                         const TArray<ETriggerEvent>& InTriggerEvents)
{
	for (const auto& TriggerEvent : InTriggerEvents)
	{
		FString FUNC_NAME;
		// 根据需要绑定的类型通过反射进行对应函数的绑定
		switch (TriggerEvent)
		{
		case ETriggerEvent::Triggered:
			FUNC_NAME = TEXT("OnInputTriggeredDo");
		case ETriggerEvent::Started:
			FUNC_NAME = TEXT("OnInputStartedDo");
		case ETriggerEvent::Ongoing:
			FUNC_NAME = TEXT("OnInputOngoingDo");
		case ETriggerEvent::Canceled:
			FUNC_NAME = TEXT("OnInputCanceledDo");
		case ETriggerEvent::Completed:
			FUNC_NAME = TEXT("OnInputCompletedDo");
		default:
			FUNC_NAME = TEXT("");
		}
		if (FUNC_NAME.IsEmpty())
		{
			UE_LOG(LogFrameworkComponentBindPlayerInput, Warning, TEXT("绑定失败，存在不合法的触发类型"));
			continue;
		}
		InputComponent->BindAction(InInputAction, TriggerEvent, InComponent, FName(FUNC_NAME));
	}
}
