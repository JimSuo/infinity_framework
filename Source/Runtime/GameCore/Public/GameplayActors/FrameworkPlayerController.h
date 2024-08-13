#pragma once

#include "CoreMinimal.h"

#include "LuaNetSerialization.h"
#include "LuaOverriderInterface.h"
#include "ModularPlayerController.h"
#include "GameFramework/PlayerController.h"

#include "FrameworkPlayerController.generated.h"

UCLASS(BlueprintType, Blueprintable, Config=GameCore)
class FRAMEWORKGAMECORE_API AFrameworkPlayerController : public AModularPlayerController, public ILuaOverriderInterface
{
	GENERATED_UCLASS_BODY()

public:
	
	//~ Common
	virtual void ReceivedPlayer() override;	
	virtual void SetPawn(APawn* InPawn) override;
	virtual void OnPossess(class APawn* APawn) override;
	virtual void OnUnPossess() override;
protected:
	virtual void OnRep_PlayerState() override;
	//~ Common End
	
public:
	//~ slua
	virtual void PostInitializeComponents() override;
	void PostLuaHook() override { ; }
	virtual FString GetLuaFilePath_Implementation() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(Replicated)
	FLuaNetSerialization LuaNetSerialization;
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
	FString LuaFilePath;
	//~ slua End

	
};
