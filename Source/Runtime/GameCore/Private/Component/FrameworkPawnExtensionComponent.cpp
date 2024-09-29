// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.


#include "FrameworkPawnExtensionComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FrameworkGameCore.h"
#include "ListenPlayerInput.h"


class UEnhancedInputLocalPlayerSubsystem;

UFrameworkPawnExtensionComponent::UFrameworkPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

/* Static */UFrameworkPawnExtensionComponent* UFrameworkPawnExtensionComponent::FindPawnExtensionComponent(const APawn* InPawn)
{
	return InPawn == nullptr ? nullptr : InPawn->FindComponentByClass<UFrameworkPawnExtensionComponent>();
}

/* Static */void UFrameworkPawnExtensionComponent::SetupPlayerInputComponent(const APawn* InPawn,
	UInputComponent* InInputComponent)
{
	// 尝试获取Pawn身上的UFrameworkPawnExtensionComponent组件对象
	auto* Component = UFrameworkPawnExtensionComponent::FindPawnExtensionComponent(InPawn);
	if (Component == nullptr)
	{
		UE_LOG(LogFrameworkGameCore, Warning, TEXT("不包含PawnExtensionComponent，自身上所有实现了IListenPlayerInput接口的Component的输入不会被绑定响应。"));
		return;
	}
	// TODO::后续为框架配置Debug命令行实现通过命令行控制Log输出
	auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(InInputComponent);
	if (EnhancedInputComp == nullptr)
	{
		UE_LOG(LogFrameworkGameCore, Error, TEXT("获取增强输入组件失败，请检查项目设置。"));
		return;
	}
	UE_LOG(LogFrameworkGameCore, Log, TEXT("包含PawnExtensionComponent，绑定自身上所有实现了IListenPlayerInput接口的Component的输入响应。"));
	Component->SetupPlayerInputComponent(EnhancedInputComp);
}

void UFrameworkPawnExtensionComponent::SetupPlayerInputComponent(UEnhancedInputComponent* InEnhancedInputComponent) const
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
