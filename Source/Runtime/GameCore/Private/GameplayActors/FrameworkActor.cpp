#include "FrameworkActor.h"

#include "LuaState.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkActor)

AFrameworkActor::AFrameworkActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AFrameworkActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (EnableLuaTick)
    {
        UnRegistLuaTick();
    }
}

FString AFrameworkActor::GetLuaFilePath_Implementation() const
{
    return ActorLuaFilePath;
}

void AFrameworkActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkActor::RegistLuaTick(float TickInterval)
{
    EnableLuaTick = true;
    auto state = NS_SLUA::LuaState::get();
    state->registLuaTick(this, TickInterval);
}

void AFrameworkActor::UnRegistLuaTick()
{
    auto state = NS_SLUA::LuaState::get();
    state->unRegistLuaTick(this);
}

void AFrameworkActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkActor, LuaNetSerialization, COND_None);
    }
}
