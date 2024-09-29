using UnrealBuildTool;
using System.IO;

public class FrameworkLua : ModuleRules
{
    public FrameworkLua(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Delegate"));
        
        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject/Widget"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject/Subsystem"),
            Path.Combine(ModuleDirectory, "Public/FunctionLibrary"),
            Path.Combine(ModuleDirectory, "Public/Interface"),
            Path.Combine(ModuleDirectory, "Public/Macro"),
        });
        
        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Private"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject/Widget"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject/Subsystem"),
            Path.Combine(ModuleDirectory, "Private/FunctionLibrary"),
            Path.Combine(ModuleDirectory, "Private/Interface"),
            Path.Combine(ModuleDirectory, "Private/Settings"),
        });
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "InfinityFramework",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "FrameworkHelper",
                "CommonUI",
                "UMG",
                "slua_unreal",
                "slua_profile",
                "DeveloperSettings"
            }
        );
    }
}