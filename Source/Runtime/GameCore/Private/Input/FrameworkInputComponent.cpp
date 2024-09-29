#include "FrameworkInputComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkInputComponent)

UFrameworkInputComponent::UFrameworkInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UFrameworkInputComponent::SetupPlayerInput(APlayerController* InPlayerController)
{
	
}

void UFrameworkInputComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UFrameworkInputComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

