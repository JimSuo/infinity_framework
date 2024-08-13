#pragma once

// 添加绑定------------------------------

/**
 * @brief 绑定以BindUObject的形式添加Debug信息到FDC中的监听
 * @param className 类名
 * @param funcName 方法名
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_UOBJECT(className, funcName)\
	if (!funcName().IsEmpty())\
	{\
		FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT(#className), TEXT(#funcName), GetUniqueID())).BindUObject(this, &className::funcName);\
	}

/**
 * @brief 绑定以传入对象并且以BindUObject的形式添加Debug信息到FDC中的监听
 * @param uObject 传入的UObject对象
 * @param className 类名
 * @param funcName 方法名
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_UOBJECT_WITH_OBJECT(uObject, className, funcName)\
	FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT((#className), TEXT(#funcName), object->GetUniqueID())).BindUObject(object, &className::funcName);

/**
 * @brief 绑定以BindLambda的形式添加Debug信息到FDC中的监听\n
 * example:\n ADD_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA(UTestClass, FName(TEXT("TestFunc")), [=]()->TArray<FString>{ TArray<FString> Arr; return Arr;})
 * @param className 类名
 * @param lambdaTagName Lambda表达式的Tag(FName类型)
 * @param lambdaContent Lambda表达式的内容
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA(className, lambdaTagName, lambdaContent)\
	FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT(#className), *lambdaTagName.ToString(), GetUniqueID())).BindLambda(lambdaContent);

/**
 * @brief 绑定以传入对象并且以BindLambda的形式添加Debug信息到FDC中的监听
 * @param uObject 传入的UObject对象
 * @param lambdaTagName Lambda表达式的Tag(FName类型)
 * @param lambdaContent Lambda表达式的内容
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA_WITH_OBJECT(uObject, lambdaTagName, lambdaContent)\
	FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%s.%d"), *uObject->GetName(), *lambdaTagName.ToString(), uObject->GetUniqueID())).BindLambda(lambdaContent);

/**
 * @brief 自定义绑定委托对象添加Debug信息到FDC中的监听
 * @param customTagName 自定义的Tag(FName类型)
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_CUSTOM(customTagName)\
	FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%d"), *customTagName.ToString(), GetUniqueID()))

/**
 * @brief 传入对象并自定义绑定委托对象添加Debug信息到FDC中的监听
 * @param uObject 传入的UObject对象
 * @param customTagName 自定义的Tag(FName类型)
 */
#define _ADD_GAMEPLAY_DEBUG_INFO_BIND_CUSTOM_WITH_OBJECT(uObject, customTagName)\
	FGameplayDebuggerCategory_Framework::AddOnCollectData(FString::Printf(TEXT("%s.%d"), *customTagName.ToString(), uObject->GetUniqueID()))

// 解除绑定------------------------------

/**
 * @brief 解除以BindUObject的形式添加Debug信息到FDC中的监听
 * @param className 类名
 * @param funcName 方法名
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_UOBJECT(className, funcName)\
	if (!funcName().IsEmpty())\
	{\
		FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT(#className), TEXT(#funcName), GetUniqueID()));\
	}

/**
 * @brief 解除以传入对象并且以BindUObject的形式添加Debug信息到FDC中的监听
 * @param uObject 传入的UObject对象
 * @param className 类名
 * @param funcName 方法名
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_UOBJECT_WITH_OBJECT(uObject, className, funcName)\
	FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT(#className), TEXT(#funcName), uObject->GetUniqueID()));

/**
 * @brief 解除以BindLambda的形式添加Debug信息到FDC中的监听
 * @param className 类名
 * @param lambdaTagName Lambda表达式的Tag(FName类型)
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA(className, lambdaTagName)\
	FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%s.%d"), TEXT(#className), *lambdaTagName.ToString(), GetUniqueID()));

/**
 * @brief 解除以传入对象并且以BindLambda的形式添加Debug信息到FDC中的监听
 * @param uObject 传入的UObject对象
 * @param lambdaTagName Lambda表达式的Tag(FName类型)
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA_WITH_OBJECT(uObject, lambdaTagName)\
	FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%s.%d"), *uObject->GetName(), *lambdaTagName.ToString(), uObject->GetUniqueID()));

/**
 * @brief 解除自定义的监听
 * @param uObject 传入的UObject对象
 * @param customTagName 自定义的Tag(FName类型)
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_CUSTOM(customTagName)\
	FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%d"), *customTagName.ToString(), GetUniqueID()));

/**
 * @brief 解除以传入UObject形式自定义绑定的监听
 * @param uObject 传入的UObject对象
 * @param customTagName 自定义的Tag(FName类型)
 */
#define _REMOVE_GAMEPLAY_DEBUG_INFO_BIND_CUSTOM_WITH_OBJECT(uObject, customTagName)\
	FGameplayDebuggerCategory_Framework::RemoveOnCollectData(FString::Printf(TEXT("%s.%d"), *customTagName.ToString(), uObject->GetUniqueID()));