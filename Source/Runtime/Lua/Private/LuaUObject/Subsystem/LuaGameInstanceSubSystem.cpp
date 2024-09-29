#include "LuaGameInstanceSubsystem.h"

ULuaGameInstanceSubSystem::ULuaGameInstanceSubSystem() : Super()
{
}

FString ULuaGameInstanceSubSystem::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}
