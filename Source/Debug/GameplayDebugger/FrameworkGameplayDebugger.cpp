#include "FrameworkGameplayDebugger.h"

#include "GameplayDebugger.h"
#include "GameplayDebuggerCategory_Framework.h"

#define LOCTEXT_NAMESPACE "FFrameworkGameplayDebuggerModule"

void FFrameworkGameplayDebuggerModule::StartupModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
	GameplayDebuggerModule.RegisterCategory(FGameplayDebuggerCategory_Framework::GameplayDebuggerCategoryName,
											IGameplayDebugger::FOnGetCategory::CreateStatic(
												&FGameplayDebuggerCategory_Framework::MakeInstance),
											EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
#endif
}

void FFrameworkGameplayDebuggerModule::ShutdownModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
	GameplayDebuggerModule.UnregisterCategory(FGameplayDebuggerCategory_Framework::GameplayDebuggerCategoryName);
#endif
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FFrameworkGameplayDebuggerModule, FrameworkGameplayDebugger)

DEFINE_LOG_CATEGORY(LogFrameworkGameplayDebugger);