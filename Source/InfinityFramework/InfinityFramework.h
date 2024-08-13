#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief InfinityFramework(F_Framework)模块, 框架的主模块, 包含框架的最基础信息。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FInfinityFrameworkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
