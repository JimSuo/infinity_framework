#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayMessageTypes2.h"
#include "UObject/WeakObjectPtr.h"
#include "GameplayTagContainer.h"

#include "GameplayMessageSubsystem.generated.h"

class UGameplayMessageSubsystem;
struct FFrame;

/**
 * @brief GameplayMessageSubsystem的Log类型
 */
GAMEPLAYMESSAGERUNTIME_API DECLARE_LOG_CATEGORY_EXTERN(LogGameplayMessageSubsystem, Log, All);

class UAsyncAction_ListenForGameplayMessage;

/**
 * @brief 可用于取消以前注册的消息监听的句柄
 * @see UGameplayMessageSubsystem::RegisterListener 和 UGameplayMessageSubsystem::UnregisterListener
 */
USTRUCT(BlueprintType)
struct GAMEPLAYMESSAGERUNTIME_API FGameplayMessageListenerHandle
{
public:
	GENERATED_BODY()

	FGameplayMessageListenerHandle() {}

	/**
	 * @brief 取消注册
	 */
	void Unregister();

	bool IsValid() const { return ID != 0; }

private:
	/**
	 * @brief 消息系统弱引用
	 */
	UPROPERTY(Transient)
	TWeakObjectPtr<UGameplayMessageSubsystem> Subsystem;

	/**
	 * @brief 消息通道
	 */
	UPROPERTY(Transient)
	FGameplayTag Channel;

	/**
	 * @brief ID
	 */
	UPROPERTY(Transient)
	int32 ID = 0;

	/**
	 * @brief 状态清除句柄
	 */
	FDelegateHandle StateClearedHandle;

	friend UGameplayMessageSubsystem;

	FGameplayMessageListenerHandle(UGameplayMessageSubsystem* InSubsystem, FGameplayTag InChannel, int32 InID) : Subsystem(InSubsystem), Channel(InChannel), ID(InID) {}
};

/** 
 * @brief 单个注册监听的信息
 */
USTRUCT()
struct FGameplayMessageListenerData
{
	GENERATED_BODY()

	/**
	 * @brief 收到消息时的回调
	 */
	TFunction<void(FGameplayTag, const UScriptStruct*, const void*)> ReceivedCallback;

	/**
	 * @brief ID
	 */
	int32 HandleID;

	/**
	 * @brief 匹配规则
	 */
	EGameplayMessageMatch MatchType;

	// Adding some logging and extra variables around some potential problems with this
	TWeakObjectPtr<const UScriptStruct> ListenerStructType = nullptr;
	bool bHadValidType = false;
};

/**
 * @brief 消息系统，此系统允许事件发起者和侦听者注册消息，而无需直接了解彼此，但他们必须就消息的类型（USTRUCT()）达成一致
 * @note 可以从游戏实例中获取消息路由器：UGameInstance::GetSubsystem<UGameplayMessageSubsystem>(GameInstance),
 *		 或直接从任何有WorldContext的UObject中获取消息路由器：UGameplayMessageSubsystem::Get（WorldContextObject）
 * @warning 请注意，当同一消息频道有多个监听时，无法保证呼叫顺序，并且可能会随着时间的推移而改变
 */
UCLASS()
class GAMEPLAYMESSAGERUNTIME_API UGameplayMessageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	friend UAsyncAction_ListenForGameplayMessage;

public:
	/**
	 * @brief 获取消息管理器实例
	 * @param WorldContextObject 上下文对象
	 * @return 消息管理器引用
	 */
	static UGameplayMessageSubsystem& Get(const UObject* WorldContextObject);

	/**
	 * @brief 是否被实例化创建
	 * @param WorldContextObject 上下文对象
	 * @return 是否被实例化创建
	 */
	static bool HasInstance(const UObject* WorldContextObject);

	//~ USubsystem Interface Begin
	virtual void Deinitialize() override;
	//~ USubsystem Interface End

	/**
	 * @brief 在指定频道上广播消息
	 * @param Channel 要广播的消息频道
	 * @param Message 要发送的消息（必须是此通道的监听器预期的相同类型的 UScriptStruct，否则将记录错误）
	 */
	template <typename FMessageStructType>
	void BroadcastMessage(FGameplayTag Channel, const FMessageStructType& Message)
	{
		const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
		BroadcastMessageInternal(Channel, StructType, &Message);
	}

	/**
	 * @brief 注册以在指定频道上接收消息
	 * @param Channel 要监听的消息通道
	 * @param Callback 接收广播消息时调用的回调（必须是消息管理器为此频道提供的相同类型的 UScriptStruct，否则将记录错误）
	 * @return 可用于注销此监听器的句柄（通过在句柄上调用 Unregister() 或直接在管理器上调用 UnregisterListener(Handle)）
	 */
	template <typename FMessageStructType>
	FGameplayMessageListenerHandle RegisterListener(FGameplayTag Channel, TFunction<void(FGameplayTag, const FMessageStructType&)>&& Callback, EGameplayMessageMatch MatchType = EGameplayMessageMatch::ExactMatch)
	{
		auto ThunkCallback = [InnerCallback = MoveTemp(Callback)](FGameplayTag ActualTag, const UScriptStruct* SenderStructType, const void* SenderPayload)
		{
			InnerCallback(ActualTag, *reinterpret_cast<const FMessageStructType*>(SenderPayload));
		};

		const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
		return RegisterListenerInternal(Channel, ThunkCallback, StructType, MatchType);
	}

	/**
	 * @brief 注册以在指定频道上接收消息，并使用指定的成员函数进行处理
	 * @note 在触发回调之前会执行弱对象有效性检查，以确保注册函数的对象仍然存在
	 * @param Channel 要监听的消息通道
	 * @param Object 要在其上调用函数的对象实例
	 * @param Function 当有人广播消息时，使用消息调用的成员函数（必须是消息管理器为此频道提供的相同类型的 UScriptStruct，否则将记录错误）
	 * @return 可用于注销此监听器的句柄（通过在句柄上调用 Unregister() 或直接在管理器上调用 UnregisterListener(Handle)）
	 */
	template <typename FMessageStructType, typename TOwner = UObject>
	FGameplayMessageListenerHandle RegisterListener(FGameplayTag Channel, TOwner* Object, void(TOwner::* Function)(FGameplayTag, const FMessageStructType&))
	{
		TWeakObjectPtr<TOwner> WeakObject(Object);
		return RegisterListener<FMessageStructType>(Channel,
			[WeakObject, Function](FGameplayTag Channel, const FMessageStructType& Payload)
			{
				if (TOwner* StrongObject = WeakObject.Get())
				{
					(StrongObject->*Function)(Channel, Payload);
				}
			});
	}

	/**
	 * @brief 注册以在指定通道上接收具有额外参数的消息，以支持高级行为
	 * @note The stateful part of this logic should probably be separated out to a separate system
	 * @param Channel 要监听的消息通道
	 * @param Params 包含高级行为信息的结构
	 * @return 可用于注销此监听器的句柄（通过在句柄上调用 Unregister() 或直接在管理器上调用 UnregisterListener(Handle)）
	 */
	template <typename FMessageStructType>
	FGameplayMessageListenerHandle RegisterListener(FGameplayTag Channel, FGameplayMessageListenerParams<FMessageStructType>& Params)
	{
		FGameplayMessageListenerHandle Handle;

		// Register to receive any future messages broadcast on this channel
		if (Params.OnMessageReceivedCallback)
		{
			auto ThunkCallback = [InnerCallback = Params.OnMessageReceivedCallback](FGameplayTag ActualTag, const UScriptStruct* SenderStructType, const void* SenderPayload)
			{
				InnerCallback(ActualTag, *reinterpret_cast<const FMessageStructType*>(SenderPayload));
			};

			const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
			Handle = RegisterListenerInternal(Channel, ThunkCallback, StructType, Params.MatchType);
		}

		return Handle;
	}

	/**
	 * @brief 取消通过 RegisterListener(...) 注册的消息监听器
	 * @param Handle 监听器句柄
	 */
	void UnregisterListener(FGameplayMessageListenerHandle Handle);

protected:
	/**
	 * @brief 在指定频道上广播消息
	 * @note 蓝图节点
	 * @param Channel 要广播的消息频道
	 * @param Message 要发送的消息（必须是此通道的监听器预期的相同类型的 UScriptStruct，否则将记录错误）
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category=Messaging, meta=(CustomStructureParam="Message", AllowAbstract="false", DisplayName="Broadcast Message"))
	void K2_BroadcastMessage(FGameplayTag Channel, const int32& Message);

	DECLARE_FUNCTION(execK2_BroadcastMessage);

private:
	// 消息通知的内部实现
	void BroadcastMessageInternal(FGameplayTag Channel, const UScriptStruct* StructType, const void* MessageBytes);

	// 注册消息通知的内部实现
	FGameplayMessageListenerHandle RegisterListenerInternal(
		FGameplayTag Channel, 
		TFunction<void(FGameplayTag, const UScriptStruct*, const void*)>&& Callback,
		const UScriptStruct* StructType,
		EGameplayMessageMatch MatchType);

	// 取消注册消息通知的内部实现
	void UnregisterListenerInternal(FGameplayTag Channel, int32 HandleID);

private:
	// 给定频道的所有信息的列表
	struct FChannelListenerList
	{
		TArray<FGameplayMessageListenerData> Listeners;
		int32 HandleID = 0;
	};

private:
	// 监听映射表
	TMap<FGameplayTag, FChannelListenerList> ListenerMap;
};
