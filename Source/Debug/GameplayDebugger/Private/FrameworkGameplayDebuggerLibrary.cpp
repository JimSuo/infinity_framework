// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkGameplayDebuggerLibrary.h"

#include "GameplayDebuggerCategory_Framework.h"
#include "Macro/FrameworkGameplayDebugHelperMacro.h"

const FName UFrameworkGameplayDebuggerLibrary::FrameworkGameplayDebuggerLibraryLambdaTag = FName(TEXT("BindFromBlueprintFunctionLibrary"));

void UFrameworkGameplayDebuggerLibrary::AddCustomGameplayDebugger(UObject* InObject,
                                                                  FOnGameplayDebug OnGameplayDebugDo,
                                                                  bool& OutResult)
{
#if WITH_GAMEPLAY_DEBUGGER_MENU
	if (!IsValid(InObject))
	{
		UE_LOG(LogFrameworkGameplayDebugger, Error, TEXT("Object为空!!!"))
		OutResult = false;
		return;
	}
	_ADD_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA_WITH_OBJECT(InObject, UFrameworkGameplayDebuggerLibrary::FrameworkGameplayDebuggerLibraryLambdaTag,
													[=]()-> TArray<FString>
													{
													TArray<FString> Infos;
													if (OnGameplayDebugDo.IsBound())
													{
													Infos = OnGameplayDebugDo.Execute();
													}
													return Infos;
													})
	OutResult = true;
#endif	
}

void UFrameworkGameplayDebuggerLibrary::RemoveCustomGameplayDebugger(UObject* InObject, bool& OutResult)
{
#if WITH_GAMEPLAY_DEBUGGER_MENU
	if (!IsValid(InObject))
	{
		UE_LOG(LogFrameworkGameplayDebugger, Error, TEXT("Object为空!!!"))
		OutResult = false;
		return;
	}
	_REMOVE_GAMEPLAY_DEBUG_INFO_BIND_LAMBDA_WITH_OBJECT(InObject,
	                                                    UFrameworkGameplayDebuggerLibrary::FrameworkGameplayDebuggerLibraryLambdaTag);
	OutResult = true;
#endif
}
