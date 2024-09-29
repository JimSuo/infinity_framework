#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"
#include "LuaOverriderInterface.h"

#include "LuaLocalPlayerSubsystem.generated.h"

UCLASS(Abstract)
class FRAMEWORKLUA_API ULuaLocalPlayerSubsystem : public ULocalPlayerSubsystem, public ILuaOverriderInterface
{
	GENERATED_BODY()

public:
	ULuaLocalPlayerSubsystem();
	
	//~ sLua Interface Begin
	
public:
	virtual FString GetLuaFilePath_Implementation() const override;
	
	//~ sLua Interface End

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};
