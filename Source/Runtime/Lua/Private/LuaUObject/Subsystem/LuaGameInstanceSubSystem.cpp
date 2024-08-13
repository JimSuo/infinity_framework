#include "LuaGameInstanceSubSystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LuaGameInstanceSubSystem)

ULuaGameInstanceSubSystem::ULuaGameInstanceSubSystem():Super()
{}

FString ULuaGameInstanceSubSystem::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}