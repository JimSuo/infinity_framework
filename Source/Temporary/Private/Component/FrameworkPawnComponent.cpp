#include "FrameworkPawnComponent.h"

#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkPawnComponent)

UFrameworkPawnComponent::UFrameworkPawnComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  EnableLuaTick(false)
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UFrameworkPawnComponent::InitializeComponent()
{
	Super::InitializeComponent();
	TryHook();
}

// Called when the game starts
void UFrameworkPawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFrameworkPawnComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (EnableLuaTick)
	{
		UnRegistLuaTick();
	}
}

FString UFrameworkPawnComponent::GetLuaFilePath_Implementation() const
{
	return PawnComponentLuaFilePath;
}

void UFrameworkPawnComponent::RegistLuaTick(float TickInterval)
{
	EnableLuaTick = true;
	auto state = NS_SLUA::LuaState::get();
	state->registLuaTick(this, TickInterval);
}

void UFrameworkPawnComponent::UnRegistLuaTick()
{
	auto state = NS_SLUA::LuaState::get();
	state->unRegistLuaTick(this);
}

void UFrameworkPawnComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	{
		DOREPLIFETIME_CONDITION(UFrameworkPawnComponent, LuaNetSerialization, COND_None);
	}
}
