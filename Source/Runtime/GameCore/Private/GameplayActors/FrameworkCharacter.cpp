#include "FrameworkCharacter.h"

#include "FrameworkPawnExtensionComponent.h"
#include "EnhancedInputComponent.h"
#include "FrameworkGameCore.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkCharacter)

AFrameworkCharacter::AFrameworkCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AFrameworkCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // 如果包含pawn拓展插件, 绑定自身上所有实现了IListenPlayerInput接口的Component的输入响应
    UFrameworkPawnExtensionComponent::SetupPlayerInputComponent(this, PlayerInputComponent);
}

FString AFrameworkCharacter::GetLuaFilePath_Implementation() const
{
    return CharacterLuaFilePath;
}


void AFrameworkCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkCharacter, LuaNetSerialization, COND_None);
    }
}