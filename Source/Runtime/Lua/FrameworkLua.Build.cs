using UnrealBuildTool;
using System.IO;

public class FrameworkLua : ModuleRules
{
    public FrameworkLua(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject/Widget"),
            Path.Combine(ModuleDirectory, "Public/LuaUObject/Subsystem"),
        });
        
        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Private"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject/Widget"),
            Path.Combine(ModuleDirectory, "Private/LuaUObject/Subsystem"),
        });
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CommonUI",
                "UMG",
                "slua_unreal",
                "slua_profile",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "FrameworkHelper"
            }
        );
    }
}