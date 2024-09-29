#include "LuaLocalPlayerSubsystem.h"

ULuaLocalPlayerSubsystem::ULuaLocalPlayerSubsystem() : Super()
{
}

FString ULuaLocalPlayerSubsystem::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}
