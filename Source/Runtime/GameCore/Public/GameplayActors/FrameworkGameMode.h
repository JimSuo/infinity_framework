#pragma once

#include "CoreMinimal.h"

#include "LuaOverriderInterface.h"
#include "LuaNetSerialization.h"
#include "ModularGameMode.h"

#include "FrameworkGameMode.generated.h"

/**
 * @brief 框架的GameModeBase对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkGameModeBase : public AModularGameModeBase, public ILuaOverriderInterface
{
    GENERATED_BODY()

public:
    AFrameworkGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override { ; }

    virtual FString GetLuaFilePath_Implementation() const override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};

/**
 * @brief 框架的GameMode对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkGameMode : public AModularGameMode, public ILuaOverriderInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual void PostInitializeComponents() override;
    void PostLuaHook() override { ; }

    virtual FString GetLuaFilePath_Implementation() const override;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
        FString LuaFilePath;
};
