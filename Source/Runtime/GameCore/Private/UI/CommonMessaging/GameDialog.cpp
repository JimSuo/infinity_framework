// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameDialog.h"

#include "MessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameDialog)

#define LOCTEXT_NAMESPACE "Messaging"

UGameDialogDescriptor* UGameDialogDescriptor::CreateConfirmationOk(const FText& Header, const FText& Body)
{
	auto* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	Descriptor->ButtonActions.Add(ConfirmAction);

	return Descriptor;
}

UGameDialogDescriptor* UGameDialogDescriptor::CreateConfirmationOkCancel(const FText& Header, const FText& Body)
{
	auto* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	FConfirmationDialogAction CancelAction;
	CancelAction.Result = EMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UGameDialogDescriptor* UGameDialogDescriptor::CreateConfirmationYesNo(const FText& Header, const FText& Body)
{
	auto* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);

	return Descriptor;
}

UGameDialogDescriptor* UGameDialogDescriptor::CreateConfirmationYesNoCancel(const FText& Header, const FText& Body)
{
	auto* Descriptor = NewObject<UGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	FConfirmationDialogAction CancelAction;
	CancelAction.Result = EMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UGameDialog::UGameDialog()
{

}

void UGameDialog::SetupDialog(UGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback)
{

}

void UGameDialog::KillDialog()
{

}

#undef LOCTEXT_NAMESPACE
