// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Subsystems/LocalPlayerSubsystem.h"

#include "MessagingSubsystem.generated.h"

class FSubsystemCollectionBase;
class UGameDialogDescriptor;
class UObject;

/**
 * @brief 对话框的可能结果
 */
UENUM(BlueprintType)
enum class EMessagingResult : uint8
{
	/** The "yes" button was pressed */
	Confirmed,
	/** The "no" button was pressed */
	Declined,
	/** The "ignore/cancel" button was pressed */
	Cancelled,
	/** The dialog was explicitly killed (no user input) */
	Killed,
	Unknown UMETA(Hidden)
};

DECLARE_DELEGATE_OneParam(FCommonMessagingResultDelegate, EMessagingResult /* Result */);

/**
 * @brief 消息子系统
 */
UCLASS(config = Framework)
class FRAMEWORKGAMECORE_API UMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UMessagingSubsystem() { }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void ShowConfirmation(UGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());
	virtual void ShowError(UGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());

private:

};
