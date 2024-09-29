#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief GameFeature(FR_GameFeature)框架的GameFeature模块，主要负责实现对GameFeature功能相关的封装以及接口实现。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkGameFeatureModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkGameFeature, Log, All);
