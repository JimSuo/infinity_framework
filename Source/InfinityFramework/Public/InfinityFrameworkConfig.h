#pragma once

#include "CoreMinimal.h"

/**
 * @brief 框架的基础的配置信息
 */
class INFINITYFRAMEWORK_API InfinityFrameworkConfig
{
	
public:
	//~ Unreal Config Begin
	
	/**
	 * @brief GameFeatures文件夹相对Plugins文件夹路径
	 */
	static const FString GameFeaturesFileRelativePath;
	
	//~ Unreal Config End

	//~ sLua Config Begin

	/**
	 * @todo 后续开放为映射表形式，配置不同的插件的文件相对路径（用bool值控制是否开启路径自定义）
	 * @brief GameFeatures/Plugin相对文件夹路径名称
	 */
	static const FString LuaFileRelativePath;
	/**
	 * @brief GameFeatures文件夹路径标识字符
	 * @note 仅作字符串比对用，需要和PluginOrGameFeatureLuaFileMaskStr内容一致
	*/
	static const char PluginOrGameFeatureLuaFileMaskChar;
	/**
	 * @brief GameFeatures文件夹路径标识字符
	 * @note 仅作字符串拼接用，需要和PluginOrGameFeatureLuaFileMaskChar内容一致
	*/
	static const FString PluginOrGameFeatureLuaFileMaskStr;

#if WITH_EDITOR
	/**
	 * @brief Developer文件夹路径标识字符
	 * @note 仅作字符串拼接用，需要和DevelopersFilePathMarkStr内容一致
	 * @warning 只能在Editor环境下使用
	*/
	static const char DevelopersFilePathMarkChar;
	/**
	 * @brief Developer文件夹路径标识字符
	 * @note 仅作字符串拼接用，需要和DevelopersFilePathMarkChar内容一致
	 * @warning 只能在Editor环境下使用
	*/
	static const FString DevelopersFilePathMarkStr;
#endif
	
	//~ sLua Config End

	//~ Framework Key Word Start

	static const FName FrameworkSettingsCategory;
	
	//~ Framework Key Word End

private:
	// 仅作属性定义用禁止创建实例
	InfinityFrameworkConfig(){}
};
