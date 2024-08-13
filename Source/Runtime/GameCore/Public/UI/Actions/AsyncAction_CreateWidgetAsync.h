// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "UObject/SoftObjectPtr.h"

#include "AsyncAction_CreateWidgetAsync.generated.h"

class APlayerController;
class UGameInstance;
class UUserWidget;
class UWorld;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateWidgetAsyncDelegate, UUserWidget*, UserWidget);

/**
 * @brief 异步加载Widget，加载完成后实例化，并在 OnComplete 上返回。
 * @note 蓝图节点
 */
UCLASS(BlueprintType)
class FRAMEWORKGAMECORE_API UAsyncAction_CreateWidgetAsync : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Cancel() override;

	/**
	 * @brief 异步加载Widget，加载完成后实例化，并在 OnComplete 上返回。
	 * @param WorldContextObject 上下文对象
	 * @param UserWidgetSoftClass Widget类软引用
	 * @param OwningPlayer 所属的PlayerController
	 * @param bSuspendInputUntilComplete 是否暂停输入直到界面创建完成
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"))
	static UAsyncAction_CreateWidgetAsync* CreateWidgetAsync(UObject* WorldContextObject, TSoftClassPtr<UUserWidget> UserWidgetSoftClass, APlayerController* OwningPlayer, bool bSuspendInputUntilComplete = true);

	virtual void Activate() override;

public:

	UPROPERTY(BlueprintAssignable)
	FCreateWidgetAsyncDelegate OnComplete;

private:
	
	void OnWidgetLoaded();

	FName SuspendInputToken;
	TWeakObjectPtr<APlayerController> OwningPlayer;
	TWeakObjectPtr<UWorld> World;
	TWeakObjectPtr<UGameInstance> GameInstance;
	bool bSuspendInputUntilComplete;
	TSoftClassPtr<UUserWidget> UserWidgetSoftClass;
	TSharedPtr<FStreamableHandle> StreamingHandle;
};
