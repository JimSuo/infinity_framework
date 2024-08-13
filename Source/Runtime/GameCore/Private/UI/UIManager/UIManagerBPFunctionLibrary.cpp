// Copyright Epic Games, Inc. All Rights Reserved.

#include "UIManagerBPFunctionLibrary.h"


#include "Widgets/CommonActivatableWidgetContainer.h"
#include "FrameworkUIManagerSubsystem.h"
#include "CommonInputSubsystem.h"
#include "FrameworkLocalPlayer.h"
#include "CommonInputTypeEnum.h"
#include "Engine/GameInstance.h"
#include "FrameworkUIPolicy.h"
#include "PrimaryUILayout.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UIManagerBPFunctionLibrary)

int32 UUIManagerBPFunctionLibrary::InputSuspensions = 0;

ECommonInputType UUIManagerBPFunctionLibrary::GetOwningPlayerInputType(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType();
		}
	}

	return ECommonInputType::Count;
}

bool UUIManagerBPFunctionLibrary::IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType() == ECommonInputType::Touch;
		}
	}
	return false;
}

bool UUIManagerBPFunctionLibrary::IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad;
		}
	}
	return false;
}

UCommonActivatableWidget* UUIManagerBPFunctionLibrary::PushContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(WidgetClass != nullptr))
	{
		return nullptr;
	}

	if (auto* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UFrameworkUIManagerSubsystem>())
	{
		if (auto* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (auto* RootLayout = Policy->GetRootLayout(CastChecked<UFrameworkLocalPlayer>(LocalPlayer)))
			{
				return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
			}
		}
	}

	return nullptr;
}

void UUIManagerBPFunctionLibrary::PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSoftClassPtr<UCommonActivatableWidget> WidgetClass)
{ 
	if (!ensure(LocalPlayer) || !ensure(!WidgetClass.IsNull()))
	{
		return;
	}

	if (auto* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UFrameworkUIManagerSubsystem>())
	{
		if (auto* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (auto* RootLayout = Policy->GetRootLayout(CastChecked<UFrameworkLocalPlayer>(LocalPlayer)))
			{
				const bool bSuspendInputUntilComplete = true;
				RootLayout->PushWidgetToLayerStackAsync(LayerName, bSuspendInputUntilComplete, WidgetClass);
			}
		}
	}
}

void UUIManagerBPFunctionLibrary::PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	if (!ActivatableWidget)
	{
		// Ignore request to pop an already deleted widget
		return;
	}

	if (const ULocalPlayer* LocalPlayer = ActivatableWidget->GetOwningLocalPlayer())
	{
		if (const auto* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UFrameworkUIManagerSubsystem>())
		{
			if (const auto* Policy = UIManager->GetCurrentUIPolicy())
			{
				if (auto* RootLayout = Policy->GetRootLayout(CastChecked<UFrameworkLocalPlayer>(LocalPlayer)))
				{
					RootLayout->FindAndRemoveWidgetFromLayer(ActivatableWidget);
				}
			}
		}
	}
}

ULocalPlayer* UUIManagerBPFunctionLibrary::GetLocalPlayerFromController(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		return Cast<ULocalPlayer>(PlayerController->Player);
	}

	return nullptr;
}

FName UUIManagerBPFunctionLibrary::SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason)
{
	return SuspendInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendReason);
}

FName UUIManagerBPFunctionLibrary::SuspendInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendReason)
{
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = SuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}

	return NAME_None;
}

void UUIManagerBPFunctionLibrary::ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken)
{
	ResumeInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendToken);
}

void UUIManagerBPFunctionLibrary::ResumeInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendToken)
{
	if (SuspendToken == NAME_None)
	{
		return;
	}

	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
	}
}

