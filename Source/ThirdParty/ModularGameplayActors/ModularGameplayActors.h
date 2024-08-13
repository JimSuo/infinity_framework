#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief ModularGameplayActors(F3rd_ModularGameplayActors)模块，框架的来自第三方的模块化Gameplay类型Actor模块，针对ModulerGameplay的封装。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FModularGameplayActorsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogModularGameplayActors, Log, All);