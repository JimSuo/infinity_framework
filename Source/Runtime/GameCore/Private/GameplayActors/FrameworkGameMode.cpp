#include "FrameworkGameMode.h"

#include "FrameworkCharacter.h"
#include "FrameworkGameState.h"
#include "FrameworkPlayerController.h"
#include "FrameworkPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkGameMode)

//~ GameModeBase

AFrameworkGameModeBase::AFrameworkGameModeBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GameStateClass = AFrameworkGameStateBase::StaticClass();
    PlayerControllerClass = AFrameworkPlayerController::StaticClass();
    PlayerStateClass = AFrameworkPlayerState::StaticClass();
    DefaultPawnClass = AFrameworkCharacter::StaticClass();
}

void AFrameworkGameModeBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

FString AFrameworkGameModeBase::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

//~ GameMode

AFrameworkGameMode::AFrameworkGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AFrameworkGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
    ILuaOverriderInterface::PostLuaHook();
}

FString AFrameworkGameMode::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}
