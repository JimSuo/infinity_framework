#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


/**
 * @brief FrameworkUMG(FR_UMG)模块，框架的UMG模块，提供高效率的UMG方法调用以及使用便利的UMG控件。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkUMGModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkUMG, Log, All);