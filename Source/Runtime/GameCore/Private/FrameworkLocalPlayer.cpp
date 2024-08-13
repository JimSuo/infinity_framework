// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrameworkLocalPlayer.h"

#include "GameFramework/PlayerController.h"
#include "FrameworkUIManagerSubsystem.h"
#include "Engine/GameInstance.h"
#include "FrameworkUIPolicy.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkLocalPlayer)

struct FSceneViewProjectionData;
class APlayerState;
class FViewport;
class APawn;

UFrameworkLocalPlayer::UFrameworkLocalPlayer()
	: Super(FObjectInitializer::Get())
{
}

FDelegateHandle UFrameworkLocalPlayer::CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());

	if (PC)
	{
		Delegate.Execute(this, PC);
	}

	return OnPlayerControllerSet.Add(Delegate);
}

FDelegateHandle UFrameworkLocalPlayer::CallAndRegister_OnPlayerStateSet(FPlayerStateSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());
	APlayerState* PlayerState = PC ? PC->PlayerState : nullptr;

	if (PlayerState)
	{
		Delegate.Execute(this, PlayerState);
	}
	
	return OnPlayerStateSet.Add(Delegate);
}

FDelegateHandle UFrameworkLocalPlayer::CallAndRegister_OnPlayerPawnSet(FPlayerPawnSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());
	APawn* Pawn = PC ? PC->GetPawn() : nullptr;

	if (Pawn)
	{
		Delegate.Execute(this, Pawn);
	}

	return OnPlayerPawnSet.Add(Delegate);
}

bool UFrameworkLocalPlayer::GetProjectionData(FViewport* Viewport, FSceneViewProjectionData& ProjectionData, int32 StereoViewIndex) const
{
	if (!bIsPlayerViewEnabled)
	{
		return false;
	}

	return Super::GetProjectionData(Viewport, ProjectionData, StereoViewIndex);
}

UPrimaryUILayout* UFrameworkLocalPlayer::GetRootUILayout() const
{
	if (auto* UIManager = GetGameInstance()->GetSubsystem<UFrameworkUIManagerSubsystem>())
	{
		if (auto* Policy = UIManager->GetCurrentUIPolicy())
		{
			return Policy->GetRootLayout(this);
		}
	}

	return nullptr;
}
