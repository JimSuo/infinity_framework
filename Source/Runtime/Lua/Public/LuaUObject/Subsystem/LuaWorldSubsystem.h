#pragma once

#include "CoreMinimal.h"

#include "Subsystems/WorldSubsystem.h"
#include "LuaOverriderInterface.h"

#include "LuaWorldSubsystem.generated.h"

UCLASS(Abstract)
class FRAMEWORKLUA_API ULuaWorldSubSystem : public UWorldSubsystem, public ILuaOverriderInterface
{
	GENERATED_BODY()

public:
	ULuaWorldSubSystem();
	
	//~ sLua Interface Begin
	
public:
	virtual FString GetLuaFilePath_Implementation() const override;

	//~ sLua Interface End

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};