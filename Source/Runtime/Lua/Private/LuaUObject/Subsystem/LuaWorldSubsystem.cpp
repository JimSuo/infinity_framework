#include "LuaWorldSubsystem.h"

ULuaWorldSubSystem::ULuaWorldSubSystem() : Super()
{
}

FString ULuaWorldSubSystem::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}
