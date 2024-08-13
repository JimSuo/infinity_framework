#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class SSaveFileEditorTab;
class FToolBarBuilder;
class FMenuBuilder;
class SDockTab;

/**
 * @brief FrameworkSaveFileEditor(FE_SaveFileEditor)模块, 框架的SaveFile编辑模块, 支持在Editor中预览与编辑.sav文件。
 * @author <a href="http://172.16.0.13:8099/suowei" target="_blank">@索维</a>
*/
class FFrameworkSaveFileEditorModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static FFrameworkSaveFileEditorModule& Get() {
        return FModuleManager::GetModuleChecked<FFrameworkSaveFileEditorModule>("FrameworkSaveFileEditor");
    }

    TWeakPtr<SSaveFileEditorTab> CurrentSaveFileEditorTab;

    /** This function will be bound to Command (by default it will bring up plugin window) */
    void PluginButtonClicked();

    // Deafult save directory
    FORCEINLINE static const FString GetDefaultSaveDirectory() { return FPaths::ProjectSavedDir() / TEXT("SaveGames/"); }

    // Found all *.sav file inside a directory
    static bool GetSaveGameNames(TSet<FString>& FoundSaves, FString SaveDirectory = TEXT(""));

    TSharedPtr<FTabManager> GetSaveEditorTabManager() { return SaveEditorTabManager; }

    bool IsGameStarted() { return bGameStarted; }

    static bool IsTabVisibleGlobal(FName InTabName) {
        return FGlobalTabmanager::Get()->FindExistingLiveTab(InTabName).IsValid();
    };

    static bool IsTabVisible(TWeakPtr<FTabManager> InDebuggingToolsManagerWeak, FName InTabName) {
        TSharedPtr<FTabManager> InDebuggingToolsManager = InDebuggingToolsManagerWeak.Pin();
        if (InDebuggingToolsManager.IsValid()) {
            return InDebuggingToolsManager->FindExistingLiveTab(InTabName).IsValid();
        }
        return false;
    };

    static void ToggleTabVisibility(TWeakPtr<FTabManager> InDebuggingToolsManagerWeak, FName InTabName) {
        TSharedPtr<FTabManager> InDebuggingToolsManager = InDebuggingToolsManagerWeak.Pin();
        if (InDebuggingToolsManager.IsValid()) {
            TSharedPtr<SDockTab> ExistingTab = InDebuggingToolsManager->FindExistingLiveTab(InTabName);
            if (ExistingTab.IsValid()) {
                ExistingTab->RequestCloseTab();
            } else {
                InDebuggingToolsManager->TryInvokeTab(InTabName);
            }
        }
    };

private:
    void RegisterMenus();

    TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

    // virtual void MakeMenuEntry(FMenuBuilder& menuBuilder);

    void OnPieWorldStarted(bool bIsSimulated);
    void OnPieWorldStopped(bool bIsSimulated);

private:
    bool bGameStarted = false;

    FDelegateHandle PostPIEStartedHandle;
    FDelegateHandle EndPIEHandle;
    FDelegateHandle PausePIEHandle;
    FDelegateHandle ResumePIEHandle;

    TSharedPtr<class FUICommandList> PluginCommands;
    TWeakPtr<SDockTab> SaveEditorManagerTab;

    // Manage all tab controls
    TSharedPtr<FTabManager> SaveEditorTabManager;

    // All tab level management
    TSharedPtr<FTabManager::FLayout> SaveEditorTabLayout;

    TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
    TSharedPtr<FExtender> MenuExtender;
};
