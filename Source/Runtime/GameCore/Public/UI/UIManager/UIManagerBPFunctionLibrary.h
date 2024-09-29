// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/SoftObjectPtr.h"

#include "UIManagerBPFunctionLibrary.generated.h"

// 前向声明
enum class ECommonInputType : uint8;
template <typename T> class TSubclassOf;

class UCommonActivatableWidget;
class APlayerController;
struct FGameplayTag;
class ULocalPlayer;
class UUserWidget;
class UObject;
struct FFrame;

UCLASS()
class FRAMEWORKGAMECORE_API UUIManagerBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UUIManagerBPFunctionLibrary() { }

	/**
	 * @brief 获取通用输入类型
	 * @param WidgetContextObject Widget界面上下文
	 * @return 通用输入类型
	 */
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Manager Function", meta = (WorldContext = "WidgetContextObject"))
	static ECommonInputType GetOwningPlayerInputType(const UUserWidget* WidgetContextObject);

	/**
	 * @brief 玩家是否使用触屏输入
	 * @param WidgetContextObject Widget界面上下文
	 * @return 是否使用触屏
	 */
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Manager Function", meta = (WorldContext = "WidgetContextObject"))
	static bool IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject);

	/**
	 * @brief 玩家是否使用手柄输入
	 * @param WidgetContextObject Widget界面上下文
	 * @return 是否使用手柄
	 */
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Manager Function", meta = (WorldContext = "WidgetContextObject"))
	static bool IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject);

	/**
	 * @brief 向给定的UI层级内推送内容
	 * @param LocalPlayer 本地玩家
	 * @param LayerName 层级GameplayTag
	 * @param WidgetClass 界面类
	 * @return ActivatableWidget类型界面对象
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static UCommonActivatableWidget* PushContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass);

	/**
	 * @brief 向给定的UI层级内推送内容（异步）
	 * @param LocalPlayer 本地玩家
	 * @param LayerName 层级GameTag名称
	 * @param WidgetClass 界面类型
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static void PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSoftClassPtr<UCommonActivatableWidget> WidgetClass);

	/**
	 * @brief 将界面对象从其所在的层推出（移除）
	 * @param ActivatableWidget 推出（移除）的界面对象
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static void PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget);

	/**
	 * @brief 根据玩家控制器对象获取本地玩家对象
	 * @param PlayerController 玩家控制器
	 * @return 本地玩家对象
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

	/**
	 * @brief 暂停玩家输入
	 * @param PlayerController 玩家控制器
	 * @param SuspendReason 暂停原因
	 * @return 暂停原因
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	/**
	 * @brief 暂停玩家输入
	 * @param LocalPlayer 本地玩家
	 * @param SuspendReason 暂停原因
	 * @return 暂停原因
	 */
	static FName SuspendInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendReason);

	/**
	 * @brief 恢复玩家输入
	 * @param PlayerController 玩家控制器
	 * @param SuspendToken 与暂停原因对应的token
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Manager Function")
	static void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

	/**
	 * @brief 恢复玩家输入
	 * @param LocalPlayer 本地玩家
	 * @param SuspendToken 与暂停原因对应的token
	 */
	static void ResumeInputForPlayer(ULocalPlayer* LocalPlayer, FName SuspendToken);


	/**
	 * @brief 根据路径获取CommonActivatableWidget类的软引用指针
	 * @param InPath 资源路径
	 * @return 类的软引用指针
	 */
	UFUNCTION(BlueprintCallable)
	static TSoftClassPtr<UCommonActivatableWidget> MakeCommonActivatableWidgetSoftClassRefrence(const FString& InPath);

private:
	/**
	 * @privatesection 输入暂停计数
	 */
	static int32 InputSuspensions;
};
