#include "FrameworkPawn.h"

#include "FrameworkPawnExtensionComponent.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkPawn)

AFrameworkPawn::AFrameworkPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}

FString AFrameworkPawn::GetLuaFilePath_Implementation() const
{
    return PawnLuaFilePath;
}

void AFrameworkPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 如果包含pawn拓展插件, 绑定自身上所有实现了IListenPlayerInput接口的Component的输入响应
    UFrameworkPawnExtensionComponent::SetupPlayerInputComponent(this, PlayerInputComponent);
}

void AFrameworkPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    {
        DOREPLIFETIME_CONDITION(AFrameworkPawn, LuaNetSerialization, COND_None);
    }
}
