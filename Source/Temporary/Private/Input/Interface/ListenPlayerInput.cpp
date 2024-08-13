#include "ListenPlayerInput.h"

#include "FrameworkTemporary.h"
#include "InputAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ListenPlayerInput)

void IListenPlayerInput::SetupInput(UEnhancedInputComponent* InputComponent)
{
	const auto& ObjectPaths = GetInputActionPaths_Implementation();
	// 遍历配置输入路径
	for (const auto& InputActionPath : ObjectPaths)
	{
		auto* InputAction = Cast<UInputAction>(InputActionPath.TryLoad());
		if (InputAction == nullptr)
		{
			UE_LOG(LogFrameworkTemporary, Error, TEXT("软引用路径配置错误，请确引用对象为InputAction"));
			continue;
		}
		InitPlayerInput_Implementation(InputComponent, InputAction);
	}
}
