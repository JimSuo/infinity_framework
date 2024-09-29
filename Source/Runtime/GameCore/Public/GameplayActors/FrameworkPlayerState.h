#pragma once

#include "CoreMinimal.h"

#include "LuaOverriderInterface.h"
#include "LuaNetSerialization.h"
#include "ModularPlayerState.h"

#include "FrameworkPlayerState.generated.h"

/**
 * @brief 框架的PlayerState对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkPlayerState : public AModularPlayerState, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PostInitializeComponents() override;
	void PostLuaHook() override { ; }

	virtual FString GetLuaFilePath_Implementation() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FLuaNetSerialization LuaNetSerialization;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString PlayerStateLuaFilePath;
};
