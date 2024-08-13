

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FrameworkGameInstance.generated.h"

enum class ECommonUserPrivilege : uint8;
enum class ECommonUserAvailability : uint8;
enum class ECommonUserOnlineContext : uint8;

class UCommonSession_SearchResult;
struct FOnlineResultInformation;
struct FPlatformUserId;
class UCommonUserInfo;
struct FGameplayTag;
class ULocalPlayer;

/**
 * 
 */
UCLASS(Abstract, Config = Framework)
class FRAMEWORKGAMECORE_API UFrameworkGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFrameworkGameInstance(const FObjectInitializer& ObjectInitializer);

	//~ Common User Session Request Interface Begin
	
	// 处理来自 User 的错误/警告, 可以按游戏需求重写
	UFUNCTION()
	virtual void HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message);
	// 处理来自 User 的权限更改, 可以按游戏需求重写
	UFUNCTION()
	virtual void HandlePrivilegeChanged(const UCommonUserInfo* UserInfo, ECommonUserPrivilege Privilege,
	                                    ECommonUserAvailability OldAvailability,
	                                    ECommonUserAvailability NewAvailability);
	// 处理来自 User 的初始化行为, 可以按游戏需求重写
	UFUNCTION()
	virtual void HandlerUserInitialized(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error,
	                                    ECommonUserPrivilege RequestedPrivilege,
	                                    ECommonUserOnlineContext OnlineContext);
	/**
	 * @brief 调用以重置用户和会话状态，通常是因为播放器已断开连接
	 */
	virtual void ResetUserAndSessionState();

	/**
	 * @brief 请求会话的流程
	 * @note 某些内容请求用户加入特定会话。
	 *		 此请求在 SetRequestedSession() 中处理。
	 *		 检查我们是否可以立即加入请求的会话 (CanJoinRequestedSession()).  如果可以，加入请求的会话 (JoinRequestedSession())
	 *		 如果没有可以加入的会话，缓存请求的会话，并引导游戏进入状态为可以加入的会话中 (ResetGameAndJoinRequestedSession())
	 */
	virtual void OnUserRequestedSession(const FPlatformUserId& PlatformUserId,
	                                    UCommonSession_SearchResult* InRequestedSession,
	                                    const FOnlineResultInformation& RequestedSessionResult);
	
	UCommonSession_SearchResult* GetUserRequestedSession() const { return RequestedSession; }
	/** 设置/清除请求的会话。设置后，请求会话的流程将开始。 */
	virtual void SetRequestedSession(UCommonSession_SearchResult* InRequestedSession);
	/** 检查是否可以加入请求的会话。 */
	virtual bool CanJoinRequestedSession() const;
	/** 加入请求的会话 */
	virtual void JoinRequestedSession();
	/** 使游戏进入加入请求的会话的状态。 */
	virtual void ResetGameAndJoinRequestedSession();
	//~ Common User Session Request Interface End

	
	//~ UGameInstance Interface Begin
	virtual int32 AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId) override;
	virtual bool RemoveLocalPlayer(ULocalPlayer* ExistingPlayer) override;
	virtual void ReturnToMainMenu() override;
	
protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	//~ UGameInstance Interface End
	
private:
	/**
	 * @brief 主要LocalPlayer
	 */
	TWeakObjectPtr<ULocalPlayer> PrimaryPlayer;
	/**
	 * @brief 玩家加入的会话请求
	 */
	UPROPERTY()
	TObjectPtr<UCommonSession_SearchResult> RequestedSession;
};
