#include "FrameworkGameCore.h"

#include "GameplayTagsManager.h"

#define LOCTEXT_NAMESPACE "FFrameworkGameCoreModule"

void FFrameworkGameCoreModule::StartupModule()
{
	UGameplayTagsManager::Get().AddTagIniSearchPath(FPaths::ProjectPluginsDir() / TEXT("infinity_framework/Config/Tags"));
}

void FFrameworkGameCoreModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkGameCoreModule, FrameworkGameCore)

DEFINE_LOG_CATEGORY (LogFrameworkGameCore);
