using UnrealBuildTool;
using System.IO;

public class FrameworkTemporary : ModuleRules
{
    public FrameworkTemporary(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/Input"),
            Path.Combine(ModuleDirectory, "Public/Component"),
            Path.Combine(ModuleDirectory, "Public/Input/Interface"),
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Private"),
            Path.Combine(ModuleDirectory, "Private/Input"),
            Path.Combine(ModuleDirectory, "Private/Component"),
            Path.Combine(ModuleDirectory, "Private/Input/Interface"),
        });
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "slua_unreal",
                "SlateCore",
                "EnhancedInput",
                "ModularGameplay"
            }
        );
    }
}