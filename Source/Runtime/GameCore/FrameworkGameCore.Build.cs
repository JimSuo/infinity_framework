﻿using UnrealBuildTool;
using System.IO;

public class FrameworkGameCore : ModuleRules
{
    public FrameworkGameCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/GameplayActors"),
            Path.Combine(ModuleDirectory, "Public/UI"),
            Path.Combine(ModuleDirectory, "Public/UI/Actions"),
            Path.Combine(ModuleDirectory, "Public/UI/UIManager"),
            Path.Combine(ModuleDirectory, "Public/UI/CommonMessaging"),
            Path.Combine(ModuleDirectory, "Public/UI/CommonUIExtension"),
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(ModuleDirectory, "Private"),
            Path.Combine(ModuleDirectory, "Public/GameplayActors"),
            Path.Combine(ModuleDirectory, "Private/UI"),
            Path.Combine(ModuleDirectory, "Private/UI/Actions"),
            Path.Combine(ModuleDirectory, "Private/UI/UIManager"),
            Path.Combine(ModuleDirectory, "Private/UI/CommonMessaging"),
            Path.Combine(ModuleDirectory, "Private/UI/CommonUIExtension"),
            
        });
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CommonUI",
                "slua_unreal",
                "ModularGameplayActors",
                "InputCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // 引擎模块
                "Core",
                "Engine",
                "CoreUObject",
                "EnhancedInput",
                // 对UMG的引用
                "Slate",
                "SlateCore",
                "UMG",
                // 对CommonUI的引用
                "CommonInput",
                // 框架内相关引用
                "FrameworkLua",
                "FrameworkTemporary",
                "CommonUser",
                // Gameplay相关
                "GameplayTags",
                // Lua相关
                "slua_profile",
            }
        );
    }
}