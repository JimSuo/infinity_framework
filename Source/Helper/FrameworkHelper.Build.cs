using UnrealBuildTool;
using System.IO;

public class FrameworkHelper : ModuleRules
{
	public FrameworkHelper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory),
			Path.Combine(ModuleDirectory, "Public"),
		});
        
		PrivateIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory),
			Path.Combine(ModuleDirectory, "Private"),
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});


		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
		});
	}
}
