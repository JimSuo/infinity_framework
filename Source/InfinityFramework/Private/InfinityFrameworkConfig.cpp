#include "InfinityFrameworkConfig.h"

/* static */const FString InfinityFrameworkConfig::GameFeaturesFileRelativePath = TEXT("GameFeatures/");

/* static */const FString InfinityFrameworkConfig::LuaFileRelativePath = TEXT("/Content/Lua/");
/* static */const char InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskChar = '$';
/* static */const FString InfinityFrameworkConfig::PluginOrGameFeatureLuaFileMaskStr = TEXT("$");
#if WITH_EDITOR
/* static */const char InfinityFrameworkConfig::DevelopersFilePathMarkChar = '@';
/* static */const FString InfinityFrameworkConfig::DevelopersFilePathMarkStr = TEXT("@");
#endif

/* static */const FName InfinityFrameworkConfig::FrameworkSettingsCategory = FName(TEXT("Infinity Framework"));
