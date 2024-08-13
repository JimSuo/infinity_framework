#pragma once
#include"CoreMinimal.h"
#include "FrameworkGameplayDebugger.h"

#if WITH_GAMEPLAY_DEBUGGER_MENU
#include "GameplayDebuggerCategory.h"

FRAMEWORKGAMEPLAYDEBUGGER_API DECLARE_DELEGATE_RetVal(TArray<FString>, FOnCollectDatas)

/**
 * @brief 框架GameplayDebug类型, 用于拓展Gameplay Debugger的类型支持在初始化时动态添加信息到GameplayDebugger中
 */
class FGameplayDebuggerCategory_Framework : public FGameplayDebuggerCategory
{
public:
	
	/// @brief Debugger名称
	FRAMEWORKGAMEPLAYDEBUGGER_API static const FName GameplayDebuggerCategoryName;
	/// @brief DebugInfo信息映射表
	FRAMEWORKGAMEPLAYDEBUGGER_API static TMap<FString, FOnCollectDatas> DebugKeyDelegateMap;
	// 添加绑定
	FRAMEWORKGAMEPLAYDEBUGGER_API static FOnCollectDatas& AddOnCollectData(const FString& Key)
	{
		if (DebugKeyDelegateMap.Contains(Key))
		{
			UE_LOG(LogFrameworkGameplayDebugger, Warning, TEXT("重复添加绑定, Key : %s 已经存在"), *Key);
			// 取消绑定当前函数, 方便后续绑定
			DebugKeyDelegateMap[Key].Unbind();
		}
		else
		{
			FOnCollectDatas Delegate;
			DebugKeyDelegateMap.Add(Key, Delegate);
			UE_LOG(LogFrameworkGameplayDebugger, Log, TEXT("添加了绑定, Key : %s"), *Key);	
		}
		return DebugKeyDelegateMap[Key];
	}
	// 移除绑定
	FRAMEWORKGAMEPLAYDEBUGGER_API static bool RemoveOnCollectData(const FString& Key)
	{
		if (!DebugKeyDelegateMap.Contains(Key))
		{
			UE_LOG(LogFrameworkGameplayDebugger, Error, TEXT("找不到Key : %s"), *Key);
			return false;
		}
		DebugKeyDelegateMap[Key].Unbind();
		DebugKeyDelegateMap.Remove(Key);
		UE_LOG(LogFrameworkGameplayDebugger, Log, TEXT("Key : %s 移除绑定成功"), *Key);
		return true;
	}
	
	// Debugger单例
	static FGameplayDebuggerCategory_Framework* Instance;
	
	FGameplayDebuggerCategory_Framework();
	
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void OnDataPackReplicated(int32 DataPackId) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;
	virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper) override;

	FRAMEWORKGAMEPLAYDEBUGGER_API static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	// Debug信息
	struct FDebugData
	{
		TArray<FString> StrArr;
		void Serialize(FArchive& archive);
	} DebugData;
};
#endif
