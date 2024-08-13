#include "FrameworkCharacter.h"

#include "FrameworkPawnExtensionComponent.h"
#include "EnhancedInputComponent.h"
#include "FrameworkGameCore.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkCharacter)

const FName AFrameworkCharacter::PawnExtComponentName = FName(TEXT("PawnExtensionComponent"));

AFrameworkCharacter::AFrameworkCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PawnExtComponent = CreateDefaultSubobject<UFrameworkPawnExtensionComponent>(AFrameworkCharacter::PawnExtComponentName);
}

void AFrameworkCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComp == nullptr)
    {
        UE_LOG(LogFrameworkGameCore, Error, TEXT("获取增强输入组件失败，请检查项目设置。"));
        return;
    }
    PawnExtComponent->SetupPlayerInputComponent(EnhancedInputComp);
}

FString AFrameworkCharacter::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}


void AFrameworkCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    {
        DOREPLIFETIME_CONDITION(AFrameworkCharacter, LuaNetSerialization, COND_None);
    }
}