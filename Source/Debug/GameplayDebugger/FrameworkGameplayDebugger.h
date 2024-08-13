#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief FrameworkGameplayDebugger(FD_GameplayDebugger)模块, 框架的Gameplay debug模块, 处理动态添加GameplayDebug信息的相关功能
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkGameplayDebuggerModule : public IModuleInterface
{
public:
    /**
     * @private
    */
    virtual void StartupModule() override;
    /**
     * @private
    */
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkGameplayDebugger, Log, All);