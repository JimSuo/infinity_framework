#pragma once

#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameplayMessageTypes2.generated.h"

class UGameplayMessageRouter;

/**
* @brief 消息监听器的匹配规则
*/
UENUM(BlueprintType)
enum class EGameplayMessageMatch : uint8
{
	/**
	 * @brief 完全匹配
	 * @note 注册“A.B”, 将匹配 A.B 的广播，但不匹配 A.B.C 的广播
	 */
	ExactMatch,

	/**
	 * @brief 部分匹配
	 * @note 注册“A.B”, 将匹配 A.B 的广播，但不匹配 A.B.C 的广播
	 */
	PartialMatch
};

/**
 * @brief 用于在为消息注册监听时指定高级行为的数据结构
 */
template<typename FMessageStructType>
struct FGameplayMessageListenerParams
{
	/**
	 * @brief 匹配规则
	 */
	EGameplayMessageMatch MatchType = EGameplayMessageMatch::ExactMatch;

	/**
	 * @brief 响应消息通知时触发的函数
	 */
	TFunction<void(FGameplayTag, const FMessageStructType&)> OnMessageReceivedCallback;

	/**
	 * @brief 将函数以弱引用的方式绑定消息监听
	 * @tparam TOwner 拥有者类型
	 * @param Object 拥有者指针对象
	 * @param Function 需要被设置的函数对象
	 */
	template<typename TOwner = UObject>
	void SetMessageReceivedCallback(TOwner* Object, void(TOwner::* Function)(FGameplayTag, const FMessageStructType&))
	{
		// 创建弱引用
		TWeakObjectPtr<TOwner> WeakObject(Object);
		// 绑定引用
		OnMessageReceivedCallback = [WeakObject, Function](FGameplayTag Channel, const FMessageStructType& Payload)
		{
			if (TOwner* StrongObject = WeakObject.Get())
			{
				(StrongObject->*Function)(Channel, Payload);
			}
		};
	}
};
