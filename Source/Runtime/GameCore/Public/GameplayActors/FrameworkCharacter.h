#pragma once

#include "CoreMinimal.h"

#include "LuaOverriderInterface.h"
#include "LuaNetSerialization.h"
#include "ModularCharacter.h"

#include "FrameworkCharacter.generated.h"

class UFrameworkPawnExtensionComponent;
class UInputComponent;

/**
 * @brief 框架的Character对象
 * @note 具有 ModularGameplay, Lua能力
 */
UCLASS(BlueprintType, Blueprintable)
class FRAMEWORKGAMECORE_API AFrameworkCharacter : public AModularCharacter, public ILuaOverriderInterface
{
    GENERATED_BODY()

protected:
	AFrameworkCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~ APawn Interface Begin

	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//~ APawn Interface End


public:
	//~ ILuaOverriderInterface Interface Begin

	virtual void PostLuaHook() override { ; }
    virtual FString GetLuaFilePath_Implementation() const override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~ ILuaOverriderInterface Interface End

	//~ sLua Property Begin
public:
	UPROPERTY(Replicated)
    FLuaNetSerialization LuaNetSerialization;
protected:
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "slua", meta=(ShowOnlyInnerProperties))
    FString LuaFilePath;

	//~ sLua Property End
	
private:
    //~ Framework Property Begin

	/**
     * @private Pawn行为组件名
     */
    static const FName PawnExtComponentName;
    /**
     * @brief Pawn行为组件
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework", Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UFrameworkPawnExtensionComponent> PawnExtComponent; 

	//~ Framework Property End
};
