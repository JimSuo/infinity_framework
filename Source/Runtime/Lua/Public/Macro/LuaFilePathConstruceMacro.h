#pragma once
#include "InfinityFrameworkConfig.h"

//~ Plugin Macro Define Start

/**
 * @brief 重写基于Plugin的获取Lua文件路径函数
 * @note 内部实现带有父类的LuaFilePath是否为空的检查，为想要实现蓝图类的对象提供。
 *		 因为如果在蓝图类中不重写GetLuaFilePath()，会默认调用蓝图的cpp类型基类的GetLuaFilePath()函数，导致基类的LuaFilePath不为null，从而触发sLua内部实现的loadFile部分逻辑
 * @param FName_plugin_file_name 插件文件夹名(FName)
 */
#define _GET_PLUGIN_LUA_FILE_PATH_With_SUPER_CHECK(FName_plugin_file_name)\
virtual FString GetLuaFilePath_Implementation() const override\
{\
	auto Path = Super::GetLuaFilePath_Implementation();\
	if (!LuaFilePath.IsEmpty())\
	{\
		return InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr + FName_plugin_file_name.ToString() + InfinityFrameworkConfig::LuaFileRelativePath + Path;\
	}\
	return Path;\
}

/**
 * @brief 重写基于Plugin的获取Lua文件路径函数
 * @param FName_plugin_file_name 插件文件夹名(FName)
 * @param lua_file_path_property 声明的lua文件路径属性变量
 */
#define _GET_PLUGIN_LUA_FILE_PATH(FName_plugin_file_name, lua_file_path_property)\
virtual FString GetLuaFilePath_Implementation() const override\
{\
	return InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr + FName_plugin_file_name.ToString() + InfinityFrameworkConfig::LuaFileRelativePath + lua_file_path_property;\
}

/**
 * @brief 构造基于Plugin的Lua文件相对路径
 * @param pathParam 接收新路径的参数
 * @param FName_plugin_file_name 插件文件夹名(FName)
 * @param relativeFilePath 相对于插件的Content/Lua下的路径
 */
#define _MAKE_PLUGIN_LUA_FILE_PATH(pathParam, FName_plugin_file_name, relativeFilePath)\
	auto pathParam = InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr + FName_plugin_file_name.ToString() + InfinityFrameworkConfig::LuaFileRelativePath + relativeFilePath;\

//~ Plugin Macro Define End

//~ GameFeature Macro Define Start

/**
 * @brief 重写基于GameFeature的获取Lua文件路径函数
 * @param FName_game_feature_file_name GameFeature文件夹名称(FName)
 */
#define _GET_GAME_FEATURE_LUA_FILE_PATH(FName_game_feature_file_name)\
virtual FString GetLuaFilePath_Implementation() const override\
{\
	auto Path = Super::GetLuaFilePath_Implementation();\
	if (!Path.IsEmpty())\
	{\
		return InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr + InfinityFrameworkConfig::GameFeaturesFileRelativePath + FName_game_feature_file_name.ToString() + InfinityFrameworkConfig::LuaFileRelativePath + Path;\
	}\
	return Path;\
}

/**
 * @brief 构造基于GameFeature的Lua文件相对路径
 * @param pathParam 接收新路径的参数
 * @param FName_game_feature_file_name GameFeature文件夹名称(FName)
 * @param relativeFilePath 相对于GameFeature的Content/Lua下的路径
 */
#define _MAKE_GAME_FEATURE_LUA_FILE_PATH(pathParam, FName_game_feature_file_name, relativeFilePath)\
auto pathParam = InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr + InfinityFrameworkConfig::GameFeaturesFileRelativePath + FName_game_feature_file_name.ToString() + InfinityFrameworkConfig::LuaFileRelativePath + relativeFilePath;\

//~ GameFeature Macro Define End