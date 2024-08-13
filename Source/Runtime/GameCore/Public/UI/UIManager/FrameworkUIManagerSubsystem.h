#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/SoftObjectPtr.h"

#include "FrameworkUIManagerSubsystem.generated.h"

class FSubsystemCollectionBase;
class UFrameworkLocalPlayer;
class UFrameworkUIPolicy;
class UObject;

/**
 * @brief 提供界面管理功能
 * @note 此类是抽象的，以防止创建它。如果需要使用基本功能，可以在Game层级继承此类。
 */
UCLASS(Abstract, config = Framework)
class FRAMEWORKGAMECORE_API UFrameworkUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	UFrameworkUIManagerSubsystem() { }

	//~ USubsystem Interface Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ USubsystem Interface End

	/**
	 * 获取当前UI策略
	 * @return 当前UI策略
	 */
	const UFrameworkUIPolicy* GetCurrentUIPolicy() const { return CurrentPolicy; }
	UFrameworkUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }

	// 针对LocalPlayer的响应操作
	
	virtual void NotifyPlayerAdded(UFrameworkLocalPlayer* LocalPlayer);
	virtual void NotifyPlayerRemoved(UFrameworkLocalPlayer* LocalPlayer);
	virtual void NotifyPlayerDestroyed(UFrameworkLocalPlayer* LocalPlayer);

protected:
	void SwitchToPolicy(UFrameworkUIPolicy* InPolicy);

private:
	/**
	 * @brief 当前UI策略
	 */
	UPROPERTY(Transient)
	TObjectPtr<UFrameworkUIPolicy> CurrentPolicy = nullptr;
	/**
	 * @brief 当前UI策略在DefaultFramework.ini中的UI策略类引用配置
	 */
	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<UFrameworkUIPolicy> DefaultUIPolicyClass;
};
