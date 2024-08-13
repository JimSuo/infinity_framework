#include "FrameworkPawn.h"

#include "FrameworkPawnExtensionComponent.h"
#include "EnhancedInputComponent.h"
#include "FrameworkGameCore.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkPawn)

const FName AFrameworkPawn::PawnExtComponentName = FName(TEXT("PawnExtensionComponent"));

AFrameworkPawn::AFrameworkPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PawnExtComponent = CreateDefaultSubobject<UFrameworkPawnExtensionComponent>(AFrameworkPawn::PawnExtComponentName);
}

FString AFrameworkPawn::GetLuaFilePath_Implementation() const
{
    return LuaFilePath;
}

void AFrameworkPawn::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ILuaOverriderInterface::PostLuaHook();
}

void AFrameworkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void AFrameworkPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    {
        DOREPLIFETIME_CONDITION(AFrameworkPawn, LuaNetSerialization, COND_None);
    }
}
