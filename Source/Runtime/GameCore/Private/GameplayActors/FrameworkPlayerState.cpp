#include "FrameworkPlayerState.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkPlayerState)

AFrameworkPlayerState::AFrameworkPlayerState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString AFrameworkPlayerState::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void AFrameworkPlayerState::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkPlayerState, LuaNetSerialization, COND_None);
    }
}
