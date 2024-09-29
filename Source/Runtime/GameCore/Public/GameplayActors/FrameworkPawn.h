#pragma once

#include "CoreMinimal.h"

#include "LuaOverriderInterface.h"
#include "LuaNetSerialization.h"
#include "ModularPawn.h"

#include "FrameworkPawn.generated.h"

class UInputComponent;

/**
 * @brief 框架的Pawn对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkPawn : public AModularPawn, public ILuaOverriderInterface
{
    GENERATED_BODY()

public:
	AFrameworkPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
    //~ AActor Interface Begin
	
    virtual void PostInitializeComponents() override;

	//~ AActor Interface End

    //~ APawn Interface Begin

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//~ APawn Interface End

    //~ Lua Interface Begin
    void PostLuaHook() override { ; }
    virtual FString GetLuaFilePath_Implementation() const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    //~ Lua Interface End

    //~ Lua Property Begin
    UPROPERTY(Replicated)
    FLuaNetSerialization LuaNetSerialization;
protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString PawnLuaFilePath;
    //~ Lua Property End
};
