#include "FrameworkPlayerController.h"

#include "FrameworkLocalPlayer.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkPlayerController)

AFrameworkPlayerController::AFrameworkPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AFrameworkPlayerController::ReceivedPlayer()
{
    Super::ReceivedPlayer();
    if (auto* LocalPlayer = Cast<UFrameworkLocalPlayer>(Player))
    {
        LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);

        if (PlayerState)
        {
            LocalPlayer->OnPlayerStateSet.Broadcast(LocalPlayer, PlayerState);
        }
    }
}

void AFrameworkPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (auto* LocalPlayer = Cast<UFrameworkLocalPlayer>(Player))
    {
        LocalPlayer->OnPlayerPawnSet.Broadcast(LocalPlayer, InPawn);
    }
}

void AFrameworkPlayerController::OnPossess(APawn* APawn)
{
    Super::OnPossess(APawn);

    if (auto* LocalPlayer = Cast<UFrameworkLocalPlayer>(Player))
    {
        LocalPlayer->OnPlayerPawnSet.Broadcast(LocalPlayer, APawn);
    }
}

void AFrameworkPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    if (auto* LocalPlayer = Cast<UFrameworkLocalPlayer>(Player))
    {
        LocalPlayer->OnPlayerPawnSet.Broadcast(LocalPlayer, nullptr);
    }
}

void AFrameworkPlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    if (PlayerState)
    {
        if (auto* LocalPlayer = Cast<UFrameworkLocalPlayer>(Player))
        {
            LocalPlayer->OnPlayerStateSet.Broadcast(LocalPlayer, PlayerState);
        }
    }
}

FString AFrameworkPlayerController::GetLuaFilePath_Implementation() const
{
    return PlayerControllerLuaFilePath;
}

void AFrameworkPlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkPlayerController, LuaNetSerialization, COND_None);
    }
}
