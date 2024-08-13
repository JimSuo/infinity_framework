// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"

#include "UObject/ObjectPtr.h"
#include "AsyncAction_ShowConfirmation.generated.h"

enum class EMessagingResult : uint8;

class UGameDialogDescriptor;
class ULocalPlayer;
class FText;
struct FFrame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonMessagingResultMCDelegate, EMessagingResult, Result);

/**
 * @brief 允许在蓝图中触发异步确认对话框，等待结果后可执行逻辑。
 * @note 蓝图节点
 */
UCLASS()
class UAsyncAction_ShowConfirmation : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAsyncAction_ShowConfirmation* ShowConfirmationYesNo(
		UObject* InWorldContextObject, FText Title, FText Message
	);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAsyncAction_ShowConfirmation* ShowConfirmationOkCancel(
		UObject* InWorldContextObject, FText Title, FText Message
	);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAsyncAction_ShowConfirmation* ShowConfirmationCustom(
		UObject* InWorldContextObject, UGameDialogDescriptor* Descriptor
	);

	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FCommonMessagingResultMCDelegate OnResult;

private:
	void HandleConfirmationResult(EMessagingResult ConfirmationResult);

	UPROPERTY(Transient)
	TObjectPtr<UObject> WorldContextObject;

	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> TargetLocalPlayer;

	UPROPERTY(Transient)
	TObjectPtr<UGameDialogDescriptor> Descriptor;
};
