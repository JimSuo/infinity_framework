/**
* @copyright Infinity Framework
 * 
 * @brief   这是一个Lua接口命名空间
 * 
 * 包含提供给Lua调用的cpp接口
 * 
 * @date    2024-07-03
 * 
 * @author  WangXianWei
 * @contact http://172.16.0.13:8099/root
 */

#ifndef ___CPP_INTERFACE_H___
#define ___CPP_INTERFACE_H___

#include "LuaState.h"

namespace LuaCppInterface
{
	int SetTimer(slua::lua_State *L);
	int ClearTimer(slua::lua_State *L);
	static slua::luaL_Reg cppInterfaceMethods[] = {
		{"SetTimer", SetTimer},
		{"ClearTimer", ClearTimer},
		{NULL, NULL},
	};
	void create_table(slua::lua_State* L, slua::luaL_Reg* funcs);
	int OpenLib(slua::lua_State* L);
}


#endif