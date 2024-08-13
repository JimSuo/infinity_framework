#include "GameplayDebuggerCategory_Framework.h"

#include "GameplayDebugger.h"

#if WITH_GAMEPLAY_DEBUGGER_MENU

const FName FGameplayDebuggerCategory_Framework::GameplayDebuggerCategoryName = FName(TEXT("Framework"));
TMap<FString, FOnCollectDatas> FGameplayDebuggerCategory_Framework::DebugKeyDelegateMap;
FGameplayDebuggerCategory_Framework* FGameplayDebuggerCategory_Framework::Instance = nullptr;

FGameplayDebuggerCategory_Framework::FGameplayDebuggerCategory_Framework()
{
	SetDataPackReplication(&DebugData);
}

void FGameplayDebuggerCategory_Framework::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	// 判断DebugActor是否为空
	if (DebugActor == nullptr)
	{
		return;
	}
	// Debug字符串
	TArray<FString> DebugDataStrArr;
	// 遍历委托获取DebugInfo数据列表
	for (auto Pair : DebugKeyDelegateMap)
	{
		FString DebugStr;
		auto Delegate = Pair.Value;
		// 检查绑定
		if (Delegate.IsBound())
		{
			auto Infos = Delegate.Execute();
			// 空值筛选
			if (Infos.IsEmpty())
			{
				continue;
			}
			// 开始分隔字符串
			DebugDataStrArr.Add(FString::Printf(TEXT("{red}------------------------------")));
			// 组合信息
			DebugDataStrArr.Append(Infos);
			// 结束分隔字符串
			DebugDataStrArr.Add(FString::Printf(TEXT("{red}------------------------------")));
		}
	}
	// 设置Debug输出信息
	DebugData.StrArr = DebugDataStrArr;
}

void FGameplayDebuggerCategory_Framework::OnDataPackReplicated(int32 DataPackId)
{
	MarkRenderStateDirty();
}

void FGameplayDebuggerCategory_Framework::DrawData(APlayerController* OwnerPC,
                                                   FGameplayDebuggerCanvasContext& CanvasContext)
{
	for (auto DebugStr : DebugData.StrArr)
	{
		CanvasContext.Print(DebugStr);	
	}
}

FDebugRenderSceneProxy* FGameplayDebuggerCategory_Framework::CreateDebugSceneProxy(
	const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper)
{
	return FGameplayDebuggerCategory::CreateDebugSceneProxy(InComponent, OutDelegateHelper);
}

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_Framework::MakeInstance()
{
	Instance = new FGameplayDebuggerCategory_Framework();
	return MakeShareable(Instance);
}

void FGameplayDebuggerCategory_Framework::FDebugData::Serialize(FArchive& archive)
{
	archive << StrArr;
}

#endif