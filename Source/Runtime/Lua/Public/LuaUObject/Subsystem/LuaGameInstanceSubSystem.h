#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/GameInstance.h"
#include "LuaOverriderInterface.h"

#include "LuaGameInstanceSubSystem.generated.h"

UCLASS()
class FRAMEWORKLUA_API ULuaGameInstanceSubSystem : public UGameInstanceSubsystem, public ILuaOverriderInterface
{
	GENERATED_BODY()
public:
	ULuaGameInstanceSubSystem();
	FString GetLuaFilePath_Implementation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};
