// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.


#include "FrameworkPawnExtensionComponent.h"

#include "EnhancedInputSubsystems.h"
#include "ListenPlayerInput.h"


class UEnhancedInputLocalPlayerSubsystem;

UFrameworkPawnExtensionComponent::UFrameworkPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

/* Static */UFrameworkPawnExtensionComponent* UFrameworkPawnExtensionComponent::FindPawnExtensionComponent(const AActor* InActor)
{
	return InActor == nullptr ? nullptr : InActor->FindComponentByClass<UFrameworkPawnExtensionComponent>();
}

void UFrameworkPawnExtensionComponent::SetupPlayerInputComponent(UEnhancedInputComponent* InEnhancedInputComponent)
{
	auto* PlayerController = GetController<APlayerController>();
	if (PlayerController == nullptr)
	{
		return;
	}
	// 绑定组件输入
	// 获取增强输入子系统
	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}
	// 获取所有实现ListenInput接口输入的组件
	auto ListenInputComponents = GetOwner()->GetComponentsByInterface(UListenPlayerInput::StaticClass());
	for (auto* ListenInputComponent : ListenInputComponents)
	{
		auto* ComponentInterface = Cast<IListenPlayerInput>(ListenInputComponent);
		ComponentInterface->SetupInput(InEnhancedInputComponent);
	}
}
