#include "FrameworkTemporary.h"

#define LOCTEXT_NAMESPACE "FFrameworkTemporaryModule"

void FFrameworkTemporaryModule::StartupModule()
{
    
}

void FFrameworkTemporaryModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkTemporaryModule, FrameworkTemporary)

DEFINE_LOG_CATEGORY(LogFrameworkTemporary);
