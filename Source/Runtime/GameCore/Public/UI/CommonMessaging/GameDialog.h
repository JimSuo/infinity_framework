// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CommonActivatableWidget.h"
#include "MessagingSubsystem.h"

#include "GameDialog.generated.h"

USTRUCT(BlueprintType)
struct FConfirmationDialogAction
{
	GENERATED_BODY()

public:
	/** Required: The dialog option to provide. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMessagingResult Result = EMessagingResult::Unknown;

	/** Optional: Display Text to use instead of the action name associated with the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionalDisplayText;

	bool operator==(const FConfirmationDialogAction& Other) const
	{
		return Result == Other.Result &&
			OptionalDisplayText.EqualTo(Other.OptionalDisplayText);
	}
};

/**
 * @brief 游戏对话框描述
 */
UCLASS()
class FRAMEWORKGAMECORE_API UGameDialogDescriptor : public UObject
{
	GENERATED_BODY()
	
public:
	static UGameDialogDescriptor* CreateConfirmationOk(const FText& Header, const FText& Body);
	static UGameDialogDescriptor* CreateConfirmationOkCancel(const FText& Header, const FText& Body);
	static UGameDialogDescriptor* CreateConfirmationYesNo(const FText& Header, const FText& Body);
	static UGameDialogDescriptor* CreateConfirmationYesNoCancel(const FText& Header, const FText& Body);

public:
	/** The header of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Header;
	
	/** The body of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Body;

	/** The confirm button's input action to use. */
	UPROPERTY(BlueprintReadWrite)
	TArray<FConfirmationDialogAction> ButtonActions;
};

/**
 * @brief 游戏对话框
 */
UCLASS(Abstract)
class FRAMEWORKGAMECORE_API UGameDialog : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UGameDialog();
	
	virtual void SetupDialog(UGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback);

	virtual void KillDialog();
};
