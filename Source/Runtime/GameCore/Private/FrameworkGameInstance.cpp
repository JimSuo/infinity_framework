// Fill out your copyright notice in the Description page of Project Settings.

#include "FrameworkGameInstance.h"

#include "CommonSessionSubsystem.h"
#include "GameplayTagContainer.h"
#include "CommonUserSubsystem.h"
#include "MessagingSubsystem.h"
#include "FrameworkGameCore.h"
#include "LuaStateSubsystem.h"
#include "CommonUISettings.h"
#include "FrameworkLocalPlayer.h"
#include "FrameworkUIManagerSubsystem.h"
#include "GameDialog.h"
#include "ICommonUIModule.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrameworkGameInstance)

UFrameworkGameInstance::UFrameworkGameInstance(const FObjectInitializer& ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		// 创建并初始化Lua虚拟机
		FLuaStateSubsystem& LuaStateSubsystem = FLuaStateSubsystem::GetLuaStateSubsystem();
		LuaStateSubsystem.Init(this);
	}
}

void UFrameworkGameInstance::HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message)
{
	ULocalPlayer* FirstPlayer = GetFirstGamePlayer();
	// 将严重的错误发送给第一个LocalPlayer, 并弹出错误对话框
	if (FirstPlayer && MessageType.MatchesTag(FCommonUserTags::SystemMessage_Error))
	{
		if (auto Messaging = FirstPlayer->GetSubsystem<UMessagingSubsystem>())
		{
			Messaging->ShowError(UGameDialogDescriptor::CreateConfirmationOk(Title, Message));
		}
	}
}

void UFrameworkGameInstance::HandlePrivilegeChanged(const UCommonUserInfo* UserInfo, ECommonUserPrivilege Privilege,
	ECommonUserAvailability OldAvailability, ECommonUserAvailability NewAvailability)
{
	// 默认情况下，如果第一个玩家的播放权限丢失，则显示错误并断开连接
	if (Privilege == ECommonUserPrivilege::CanPlay && OldAvailability == ECommonUserAvailability::NowAvailable && NewAvailability != ECommonUserAvailability::NowAvailable)
	{
		UE_LOG(LogFrameworkGameCore, Error, TEXT("HandlePrivilegeChanged: Player %d no longer has permission to play the game!"), UserInfo->LocalPlayerIndex);
		/* Games can do something specific in subclass */
	}
}

void UFrameworkGameInstance::HandlerUserInitialized(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error,
	ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext)
{
	/* Games can do something specific in subclass */
}

void UFrameworkGameInstance::ResetUserAndSessionState()
{
	UCommonUserSubsystem* UserSubsystem = GetSubsystem<UCommonUserSubsystem>();
	if (ensure(UserSubsystem))
	{
		UserSubsystem->ResetUserState();
	}

	auto* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
	if (ensure(SessionSubsystem))
	{
		SessionSubsystem->CleanUpSessions();
	}
}

void UFrameworkGameInstance::OnUserRequestedSession(const FPlatformUserId& PlatformUserId,
	UCommonSession_SearchResult* InRequestedSession, const FOnlineResultInformation& RequestedSessionResult)
{
	if (InRequestedSession)
	{
		// 如果会话请求有效
		SetRequestedSession(InRequestedSession);
	}
	else
	{
		HandleSystemMessage(FCommonUserTags::SystemMessage_Error,
		                    NSLOCTEXT("CommonGame", "Warning_RequestedSessionFailed", "Requested Session Failed"),
		                    RequestedSessionResult.ErrorText);
	}
}

void UFrameworkGameInstance::SetRequestedSession(UCommonSession_SearchResult* InRequestedSession)
{
	RequestedSession = InRequestedSession;
	if (RequestedSession)
	{
		if (CanJoinRequestedSession())
		{
			JoinRequestedSession();
		}
		else
		{
			ResetGameAndJoinRequestedSession();
		}
	}
}

bool UFrameworkGameInstance::CanJoinRequestedSession() const
{
	/* 按需重写 */
	return true;
}

void UFrameworkGameInstance::JoinRequestedSession()
{
	if (RequestedSession)
	{
		if (auto* const FirstPlayer = GetFirstGamePlayer())
		{
			auto* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
			if (ensure(SessionSubsystem))
			{
				// 清除当前请求会话
				UCommonSession_SearchResult* LocalRequestedSession = RequestedSession;
				RequestedSession = nullptr;
				SessionSubsystem->JoinSession(FirstPlayer->PlayerController, LocalRequestedSession);
			}
		}
	}
}

void UFrameworkGameInstance::ResetGameAndJoinRequestedSession()
{
	// 默认行为是返回到主菜单。当游戏处于就绪状态时，游戏必须调用 JoinRequestedSession()。
	ReturnToMainMenu();
}

int32 UFrameworkGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		if (!PrimaryPlayer.IsValid())
		{
			UE_LOG(LogFrameworkGameCore, Log, TEXT("AddLocalPlayer: Set %s to Primary Player, UserID : [%d]"),
			       *NewPlayer->GetName(),
			       FPlatformMisc::GetUserIndexForPlatformUser(UserId));
			PrimaryPlayer = NewPlayer;
		}
		// 通知UI管理器添加了本地玩家
		auto* UIManager = GetSubsystem<UFrameworkUIManagerSubsystem>();
		if (UIManager != nullptr)
		{
			UIManager->NotifyPlayerAdded(Cast<UFrameworkLocalPlayer>(NewPlayer));
		}
	}
	
	return ReturnVal;
}

bool UFrameworkGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	if (PrimaryPlayer == ExistingPlayer)
	{
		PrimaryPlayer.Reset();
		UE_LOG(LogFrameworkGameCore, Log, TEXT("RemoveLocalPlayer: Unsetting Primary Player from %s"), *ExistingPlayer->GetName());
	}
	auto* UIManager = GetSubsystem<UFrameworkUIManagerSubsystem>();
	if (UIManager != nullptr)
	{
		UIManager->NotifyPlayerDestroyed(Cast<UFrameworkLocalPlayer>(ExistingPlayer));
	}

	return Super::RemoveLocalPlayer(ExistingPlayer);
}

void UFrameworkGameInstance::ReturnToMainMenu()
{
	ResetUserAndSessionState();

	Super::ReturnToMainMenu();
}

void UFrameworkGameInstance::Init()
{
	Super::Init();

	// 获取CommonUI的GameplayTag容器
	FGameplayTagContainer PlatformTraits = ICommonUIModule::GetSettings().GetPlatformTraits();
	// 绑定CommonUserSubsystem消息回调
	auto* UserSubsystem = GetSubsystem<UCommonUserSubsystem>();
	if (ensure(UserSubsystem))
	{
		UserSubsystem->SetTraitTags(PlatformTraits);
		UserSubsystem->OnHandleSystemMessage.AddDynamic(this, &UFrameworkGameInstance::HandleSystemMessage);
		UserSubsystem->OnUserPrivilegeChanged.AddDynamic(this, &UFrameworkGameInstance::HandlePrivilegeChanged);
		UserSubsystem->OnUserInitializeComplete.AddDynamic(this, &UFrameworkGameInstance::HandlerUserInitialized);
	}

	UCommonSessionSubsystem* SessionSubsystem = GetSubsystem<UCommonSessionSubsystem>();
	if (ensure(SessionSubsystem))
	{
		SessionSubsystem->OnUserRequestedSessionEvent.AddUObject(this, &UFrameworkGameInstance::OnUserRequestedSession);
	}
}

void UFrameworkGameInstance::Shutdown()
{
	Super::Shutdown();
	FLuaStateSubsystem& LuaStateSubsystem = FLuaStateSubsystem::GetLuaStateSubsystem();
	LuaStateSubsystem.Close();
}
