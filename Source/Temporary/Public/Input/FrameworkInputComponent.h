// Copyright (c) Meta Platforms, Inc. and affiliates.All rights reserved. This source code is licensed under the license found in the LICENSE file in the root directory of this source tree.

#pragma once

#include "CoreMinimal.h"

#include "EnhancedInputComponent.h"

#include "FrameworkInputComponent.generated.h"


class APlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FRAMEWORKTEMPORARY_API UFrameworkInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UFrameworkInputComponent();

	void SetupPlayerInput(APlayerController* InPlayerController);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
