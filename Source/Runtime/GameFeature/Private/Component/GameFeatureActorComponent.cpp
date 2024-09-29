// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFeatureActorComponent.h"

#include "InfinityFrameworkConfig.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureActorComponent)

UGameFeatureActorComponent::UGameFeatureActorComponent(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
}

FString UGameFeatureActorComponent::GetGameFeatureName_Implementation() const
{
	return GameFeatureName.ToString();
}

FString UGameFeatureActorComponent::GetLuaFilePath_Implementation() const
{
	auto Path = Super::GetLuaFilePath_Implementation();
	if (!Path.IsEmpty())
	{
		Path = InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr +
			InfinityFrameworkConfig::GameFeaturesFileRelativePath
			+ GameFeatureName.ToString()
			+ InfinityFrameworkConfig::LuaFileRelativePath
			+ Path;
	}
	return Path;
}