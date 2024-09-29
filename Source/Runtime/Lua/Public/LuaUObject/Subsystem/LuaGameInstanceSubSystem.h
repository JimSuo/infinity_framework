#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "LuaOverriderInterface.h"

#include "LuaGameInstanceSubsystem.generated.h"

UCLASS(Abstract)
class FRAMEWORKLUA_API ULuaGameInstanceSubSystem : public UGameInstanceSubsystem, public ILuaOverriderInterface
{
	GENERATED_BODY()

public:
	ULuaGameInstanceSubSystem();
	
	//~ sLua Interface Begin
	
public:
	virtual FString GetLuaFilePath_Implementation() const override;

	//~ sLua Interface End
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "slua")
    FString LuaFilePath;
};
