// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"
#include "LuaNetSerialization.h"

#include "LuaOverriderInterface.h"
#include "Components/PawnComponent.h"

#include "FrameworkPawnComponent.generated.h"

/**
 * @brief 框架Pawn对象的组件
 * @note 具有PawnComponent能力，Lua能力
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FRAMEWORKGAMECORE_API UFrameworkPawnComponent : public UPawnComponent, public ILuaOverriderInterface
{
	GENERATED_BODY()

public:
	UFrameworkPawnComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~ ActorComponent Interface Begin
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ ActorComponent Interface End

public:
	//~ sLua Interface Begin
	FString GetLuaFilePath_Implementation() const override;
	UFUNCTION(Blueprintcallable)
	void RegistLuaTick(float TickInterval);
	UFUNCTION(Blueprintcallable)
	void UnRegistLuaTick();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~ sLua Interface End
	
protected:
	//~ sLua Property Begin
	UPROPERTY(Replicated)
	FLuaNetSerialization LuaNetSerialization;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "slua|Components")
	FString PawnComponentLuaFilePath;
private:
	bool EnableLuaTick;
	//~ sLua Property End
};
