#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief FrameworkTemporary(FR_Temporary)模块，框架的临时脚本模块，提供临时的处理方式，如使用需要关注内容的变更，非必要情况避免使用。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkTemporaryModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

/**
 * @privatesection
*/
DECLARE_LOG_CATEGORY_EXTERN(LogFrameworkTemporary, Log, All);
