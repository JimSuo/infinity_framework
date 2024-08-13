// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/LocalPlayer.h"

#include "FrameworkLocalPlayer.generated.h"

// TODO::补全剩余需求的Gameplay类型

struct FSceneViewProjectionData;
class UPrimaryUILayout;
class APlayerController;
class APlayerState;
class FViewport;
class UObject;
class APawn;

/**
 * @brief 框架的LocalPlayer对象, 包含对输入以及UI框架的处理。
 */
UCLASS(config=Engine, transient)
class FRAMEWORKGAMECORE_API UFrameworkLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	UFrameworkLocalPlayer();
	
	/**
	 * @brief 当 LocalPlayer 分配 PlayerController 时执行
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UFrameworkLocalPlayer* LocalPlayer, APlayerController* PlayerController);
	FPlayerControllerSetDelegate OnPlayerControllerSet;

	/**
	 * @brief 当 LocalPlayer 分配 PlayerState 时执行
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerStateSetDelegate, UFrameworkLocalPlayer* LocalPlayer, APlayerState* PlayerState);
	FPlayerStateSetDelegate OnPlayerStateSet;
	
	/**
	 * @brief 当 LocalPlayer 分配 Pawn 时执行
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerPawnSetDelegate, UFrameworkLocalPlayer* LocalPlayer, APawn* Pawn);
	FPlayerPawnSetDelegate OnPlayerPawnSet;

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerStateSet(FPlayerStateSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerPawnSet(FPlayerPawnSetDelegate::FDelegate Delegate);

public:
	virtual bool GetProjectionData(FViewport* Viewport, FSceneViewProjectionData& ProjectionData, int32 StereoViewIndex) const override;

	bool IsPlayerViewEnabled() const { return bIsPlayerViewEnabled; }
	void SetIsPlayerViewEnabled(bool bInIsPlayerViewEnabled) { bIsPlayerViewEnabled = bInIsPlayerViewEnabled; }

	UPrimaryUILayout* GetRootUILayout() const;

private:
	bool bIsPlayerViewEnabled = true;
};
