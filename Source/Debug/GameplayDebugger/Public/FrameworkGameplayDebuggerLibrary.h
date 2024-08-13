#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrameworkGameplayDebuggerLibrary.generated.h"

/**
 * @private GameplayDebug进行时执行的事件
*/
DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<FString>, FOnGameplayDebug);


/**
 * @brief FrameworkGameplayDebugger(FGD)蓝图函数库
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
 */
UCLASS()
class FRAMEWORKGAMEPLAYDEBUGGER_API UFrameworkGameplayDebuggerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	/// @brief 从蓝图方法库添加的Lambda绑定的统一LambdaTag
	static const FName FrameworkGameplayDebuggerLibraryLambdaTag;
	

public:
	/**
	* @brief 添加自定义GameplayDebugger信息
	* @param InObject 添加debug信息的UObject对象
	* @param OnGameplayDebugDo GameplayDebugger开启时执行的事件
	* @param[out] OutResult 是否成功添加
	*/
	UFUNCTION(BlueprintCallable, Category="Framework | GameplayDebugger", meta=(DisplayName = "Add Custom Gameplay Debugger"))
	static void AddCustomGameplayDebugger(UObject* InObject, FOnGameplayDebug OnGameplayDebugDo, bool& OutResult);
	
	/// @brief 移除自定义GameplayDebugger信息
	/// @param InObject 移除ebug信息的UObject对象
	/// @param[out] OutResult 是否成功移除
	UFUNCTION(BlueprintCallable, Category="Framework | GameplayDebugger", meta=(DisplayName = "Remove Custom Gameplay Debugger"))
	static void RemoveCustomGameplayDebugger(UObject* InObject, bool& OutResult);
};
