// Copyright Epic Games, Inc. All Rights Reserved.
#include "ModularHUD.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Async/TaskGraphInterfaces.h"
#include "UObject/UObjectIterator.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularHUD)

class AActor;
class UWorld;

AModularHUD::AModularHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AModularHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularHUD::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

void AModularHUD::GetDebugActorList(TArray<AActor*>& InOutList)
{
	UWorld* World = GetWorld();

	Super::GetDebugActorList(InOutList);

	// Add all actors with an ability system component.
	for (TObjectIterator<UAbilitySystemComponent> It; It; ++It)
	{
		if (UAbilitySystemComponent* ASC = *It)
		{
			if (!ASC->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
			{
				AActor* AvatarActor = ASC->GetAvatarActor();
				AActor* OwnerActor = ASC->GetOwnerActor();

				if (AvatarActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(AvatarActor))
				{
					AddActorToDebugList(AvatarActor, InOutList, World);
				}
				else if (OwnerActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor))
				{
					AddActorToDebugList(OwnerActor, InOutList, World);
				}
			}
		}
	}
}

