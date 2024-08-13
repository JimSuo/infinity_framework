#include "FrameworkGameState.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkGameState)

AFrameworkGameStateBase::AFrameworkGameStateBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AFrameworkGameStateBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
    ILuaOverriderInterface::PostLuaHook();
}

FString AFrameworkGameStateBase::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void AFrameworkGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkGameStateBase, LuaNetSerialization, COND_None);
    }
}

AFrameworkGameState::AFrameworkGameState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FString AFrameworkGameState::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void AFrameworkGameState::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkGameState, LuaNetSerialization, COND_None);
    }
}
