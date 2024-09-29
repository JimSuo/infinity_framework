using System.IO;
using UnrealBuildTool;

public class FrameworkGameFeature : ModuleRules
{
    public FrameworkGameFeature(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/Interface"),
            Path.Combine(ModuleDirectory, "Public/Component"),
            Path.Combine(ModuleDirectory, "Public/Actions"),
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Private/Interface"),
            Path.Combine(ModuleDirectory, "Private/Component"),
            Path.Combine(ModuleDirectory, "Private/Actions"),
        });
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "slua_unreal",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InfinityFramework"
            }
        );
    }
}