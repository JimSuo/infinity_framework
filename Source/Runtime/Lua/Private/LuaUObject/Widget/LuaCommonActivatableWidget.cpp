// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCommonActivatableWidget.h"

#include "FrameworkLua.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LuaCommonActivatableWidget)

bool ULuaCommonActivatableWidget::Initialize()
{
	bool bIsInited = Super::Initialize();
	if (bIsInited)
	{
		UE_LOG(LogFrameworkLua, Verbose, TEXT("UFrameworkCommonActivatableWidget[%s] Initialize [%s]!"), *GetName(), *LuaFilePath);

		if (GetSelfTable().isValid())
		{
			CallLuaFunction(TEXT("Initialize"));
		}
	}

	return bIsInited;
}

void ULuaCommonActivatableWidget::BeginDestroy()
{
	auto SelfTable = GetSelfTable();
	if (SelfTable.isValid())
	{
		auto OnDestroyFunc = SelfTable.getFromTable<NS_SLUA::LuaVar>("OnDestroy");
		if (OnDestroyFunc.isFunction())
		{
			OnDestroyFunc.call(SelfTable);
		}
		else
		{
			NS_SLUA::Log::Error("UFrameworkCommonActivatableWidget[%s] missing OnDestroy function [%s]!", TCHAR_TO_UTF8(*GetName()), TCHAR_TO_UTF8(*LuaFilePath));
		}
	}

	UE_LOG(LogFrameworkLua, Log, TEXT("UFrameworkCommonActivatableWidget[%s] BeginDestroy [%s]!"), *GetName(), *LuaFilePath);
    
	Super::BeginDestroy();
}

FString ULuaCommonActivatableWidget::GetLuaFilePath_Implementation() const
{
	return LuaFilePath;
}
