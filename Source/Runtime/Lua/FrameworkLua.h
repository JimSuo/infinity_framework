#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief FrameworkLua(FR_Lua)模块, 框架的Lua相关模块, 负责处理与sLua插件相关的逻辑。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkLuaModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkLua, Log, All);