// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class CommonUser : ModuleRules
{
	public CommonUser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bool bUseOnlineSubsystemV1 = true;

		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory),
			Path.Combine(ModuleDirectory, "Public"),
			Path.Combine(ModuleDirectory, "Public/Actions"),
		});

		PrivateIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory),
			Path.Combine(ModuleDirectory, "Private"),
			Path.Combine(ModuleDirectory, "Private/Actions"),
		});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreOnline",
				"GameplayTags",
				// ... add other public dependencies that you statically link with here ...
			}
			);

		if (bUseOnlineSubsystemV1)
		{
			PublicDependencyModuleNames.Add("OnlineSubsystem");
		}
		else
		{
			PublicDependencyModuleNames.Add("OnlineServicesInterface");
		}
		PrivateDependencyModuleNames.Add("OnlineSubsystemUtils");
		PublicDefinitions.Add("COMMONUSER_OSSV1=" + (bUseOnlineSubsystemV1 ? "1" : "0"));

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreOnline",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ApplicationCore",
				"InputCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
