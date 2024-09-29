// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrameworkUIManagerSubsystem.h"

#include "Engine/GameInstance.h"
#include "UIManagerSettings.h"
#include "FrameworkUIPolicy.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkUIManagerSubsystem)

void UFrameworkUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const auto* Settings = GetDefault<UUIManagerSettings>();
	auto UIPolicyClass = Settings->DefaultUIPolicyClass;
	if (CurrentPolicy == nullptr && UIPolicyClass.IsNull() == false)
	{
		// 加载并创建UI策略Object
		TSubclassOf<UFrameworkUIPolicy> PolicyClass = UIPolicyClass.LoadSynchronous();
		SwitchToPolicy(NewObject<UFrameworkUIPolicy>(this, PolicyClass));
	}
}

void UFrameworkUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// 清空策略
	SwitchToPolicy(nullptr);
}

bool UFrameworkUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// 判断是否为VR项目，如果是VR项目使用另一套支持VR的UI框架
	const auto* Settings = GetDefault<UUIManagerSettings>();
	if (Settings->VR)
	{
		return false;
	}
	
	// 仅在客户端创建
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UFrameworkUIManagerSubsystem::NotifyPlayerAdded(UFrameworkLocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer) && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerAdded(LocalPlayer);
	}
}

void UFrameworkUIManagerSubsystem::NotifyPlayerRemoved(UFrameworkLocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerRemoved(LocalPlayer);
	}
}

void UFrameworkUIManagerSubsystem::NotifyPlayerDestroyed(UFrameworkLocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerDestroyed(LocalPlayer);
	}
}

void UFrameworkUIManagerSubsystem::SwitchToPolicy(UFrameworkUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}

