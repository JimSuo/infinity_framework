#pragma once

/// 构造基于Plugin的Lua文件相对路径
/// @param plugin_name plugin名称
#define _GET_PLUGIN_LUA_PATH(plugin_name)\
	virtual FString GetLuaFilePath_Implementation() const override\
	{\
		auto Path = Super::GetLuaFilePath_Implementation();\
		if (!LuaFilePath.IsEmpty())\
		{\
			return TEXT("$")#plugin_name"/Content/Lua/" + Path;\
		}\
		return Path;\
	}
