#pragma once

#include "CoreMinimal.h"
#include "ModularActor.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "GameFramework/Actor.h"

#include "FrameworkActor.generated.h"

/**
 * @brief 框架的Actor对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkActor : public AModularActor, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual FString GetLuaFilePath_Implementation() const override;
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override
    {
    }

    UFUNCTION(Blueprintcallable)
        void RegistLuaTick(float TickInterval);

    UFUNCTION(Blueprintcallable)
        void UnRegistLuaTick();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
        FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString ActorLuaFilePath;

private:
    bool EnableLuaTick = false;
};
