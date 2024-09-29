#include "FrameworkGameFeature.h"

#define LOCTEXT_NAMESPACE "FFrameworkGameFeatureModule"

void FFrameworkGameFeatureModule::StartupModule()
{
    
}

void FFrameworkGameFeatureModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkGameFeatureModule, FrameworkGameFeature)

DEFINE_LOG_CATEGORY(LogFrameworkGameFeature);
