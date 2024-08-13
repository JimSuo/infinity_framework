#pragma once

/// 获取基于GameFeature的Lua文件相对路径
/// @param game_feature_name GameFeature名称
#define _GET_GAME_FEATURE_LUA_PATH(game_feature_name)\
	virtual FString GetLuaFilePath_Implementation() const override\
	{\
		auto Path = Super::GetLuaFilePath_Implementation();\
		if (!Path.IsEmpty())\
		{\
			return TEXT("$GameFeatures/")#game_feature_name"/Content/Lua/" + Path;\
		}\
		return Path;\
	}