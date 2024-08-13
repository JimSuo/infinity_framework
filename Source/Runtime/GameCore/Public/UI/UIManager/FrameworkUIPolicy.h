// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/World.h"

#include "FrameworkUIPolicy.generated.h"

class UFrameworkUIManagerSubsystem;
class UFrameworkLocalPlayer;
class UPrimaryUILayout;
class ULocalPlayer;

/**
 * @brief 本地多人交互模式
 */
UENUM()
enum class ELocalMultiplayerInteractionMode : uint8
{
	// Fullscreen viewport for the primary player only, regardless of the other player's existence
	PrimaryOnly,

	// Fullscreen viewport for one player, but players can swap control over who's is displayed and who's is dormant
	SingleToggle,

	// Viewports displayed simultaneously for both players
	Simultaneous
};

/**
 * @brief 根视图布局信息
 */
USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	/**
	 * @brief 本地玩家对象
	 */
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer = nullptr;
	/**
	 * @brief 根节点布局列表
	 */
	UPROPERTY(Transient)
	TObjectPtr<UPrimaryUILayout> RootLayout = nullptr;

	/**
	 * @brief 添加到视窗
	 */
	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UPrimaryUILayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};

/**
 * @brief UI策略类
 */
UCLASS(Abstract, Blueprintable, Within = FrameworkUIManagerSubsystem)
class FRAMEWORKGAMECORE_API UFrameworkUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 以指定类型获取UI策略
	 * @tparam GameUIPolicyClass UI泛型策略类
	 * @param WorldContextObject 上下文对象
	 * @return UI策略类
	 */
	template <typename GameUIPolicyClass = UFrameworkUIPolicy>
	static GameUIPolicyClass* GetUIPolicyAs(const UObject* WorldContextObject)
	{
		return Cast<GameUIPolicyClass>(GetUIPolicy(WorldContextObject));
	}

	/**
	 * @brief 获取UI策略对象
	 * @param WorldContextObject 上下文对象
	 * @return UI策略对象
	 */
	static UFrameworkUIPolicy* GetUIPolicy(const UObject* WorldContextObject);

public:
	/**
	 * @brief 获取世界对象
	 * @return 世界对象
	 */
	virtual UWorld* GetWorld() const override;
	/**
	 * @brief 获取拥有的UI管理器
	 * @return UIManager对象
	 */
	UFrameworkUIManagerSubsystem* GetOwningUIManager() const;
	/**
	 * @brief 获取根节点布局
	 * @param LocalPlayer 本地玩家对象
	 * @return 主要UI布局
	 */
	UPrimaryUILayout* GetRootLayout(const UFrameworkLocalPlayer* LocalPlayer) const;

	ELocalMultiplayerInteractionMode GetLocalMultiplayerInteractionMode() const { return LocalMultiplayerInteractionMode; }

	void RequestPrimaryControl(UPrimaryUILayout* Layout);

protected:
	/**
	 * @brief 添加主要布局对象到视窗
	 * @param LocalPlayer 本地玩家
	 * @param Layout 主要布局对象
	 */
	void AddLayoutToViewport(UFrameworkLocalPlayer* LocalPlayer, UPrimaryUILayout* Layout);
	/**
	 * @brief 将主要布局对象从视窗中移除
	 * @param LocalPlayer 本地玩家
	 * @param Layout 主要布局对象
	 */
	void RemoveLayoutFromViewport(UFrameworkLocalPlayer* LocalPlayer, UPrimaryUILayout* Layout);

	virtual void OnRootLayoutAddedToViewport(UFrameworkLocalPlayer* LocalPlayer, UPrimaryUILayout* Layout);
	virtual void OnRootLayoutRemovedFromViewport(UFrameworkLocalPlayer* LocalPlayer, UPrimaryUILayout* Layout);
	virtual void OnRootLayoutReleased(UFrameworkLocalPlayer* LocalPlayer, UPrimaryUILayout* Layout);
	/**
	 * @brief 创建界面布局对象
	 * @param LocalPlayer 本地玩家
	 */
	void CreateLayoutWidget(UFrameworkLocalPlayer* LocalPlayer);
	/**
	 * @brief 获取主要UI布局
	 * @param LocalPlayer 本地玩家
	 * @return 主要UI布局子类
	 */
	TSubclassOf<UPrimaryUILayout> GetLayoutWidgetClass(UFrameworkLocalPlayer* LocalPlayer);

private:
	ELocalMultiplayerInteractionMode LocalMultiplayerInteractionMode = ELocalMultiplayerInteractionMode::PrimaryOnly;

	/**
	 * @brief UI主要布局对象子类软引用
	 */
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UPrimaryUILayout> LayoutClass;

	/**
	 * @brief UI根视图布局信息
	 */
	UPROPERTY(Transient)
	TArray<FRootViewportLayoutInfo> RootViewportLayouts;

private:
	// 针对LocalPlayer的响应操作
	
	void NotifyPlayerAdded(UFrameworkLocalPlayer* LocalPlayer);
	void NotifyPlayerRemoved(UFrameworkLocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UFrameworkLocalPlayer* LocalPlayer);

	friend class UFrameworkUIManagerSubsystem;
};
