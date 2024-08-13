#include "FrameworkLua.h"

#define LOCTEXT_NAMESPACE "FFrameworkLuaModule"

void FFrameworkLuaModule::StartupModule()
{
    
}

void FFrameworkLuaModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkLuaModule, FrameworkLua)

DEFINE_LOG_CATEGORY(LogFrameworkLua);