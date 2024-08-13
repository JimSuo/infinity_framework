#pragma once

#include "CoreMinimal.h"

#include "ModularGameState.h"
#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"

#include "FrameworkGameState.generated.h"

/**
 * @brief 框架的GameStateBase对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkGameStateBase : public AModularGameStateBase, public ILuaOverriderInterface
{
    GENERATED_BODY()

public:
    AFrameworkGameStateBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override
    {
    }

    virtual FString GetLuaFilePath_Implementation() const override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
    FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};

/**
 * @brief 框架的GameState对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkGameState : public AModularGameState, public ILuaOverriderInterface
{
    GENERATED_BODY()

public:
    AFrameworkGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override
    {
    }

    virtual FString GetLuaFilePath_Implementation() const override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated)
        FLuaNetSerialization LuaNetSerialization;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
