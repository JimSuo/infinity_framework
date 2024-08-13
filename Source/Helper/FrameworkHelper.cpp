#include "FrameworkHelper.h"

#define LOCTEXT_NAMESPACE "FFrameworkHelperModule"

void FFrameworkHelperModule::StartupModule()
{
    
}

void FFrameworkHelperModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkHelperModule, FrameworkHelper)

DEFINE_LOG_CATEGORY(LogFrameworkHelper)