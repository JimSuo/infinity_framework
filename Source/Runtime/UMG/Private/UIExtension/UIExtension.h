#pragma once

#include "Logging/LogMacros.h"

// 每个子模块都会有一个子模块文件, 一切需要添加配置的子模块相关属性都在这个文件中修改

// 模块中的子模块的Log使用单独的文件封装, 避免全部都在主模块中添加Log类型注册
DECLARE_LOG_CATEGORY_EXTERN(LogUIExtension, Log, All);