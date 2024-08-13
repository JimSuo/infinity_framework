#include "LuaCppInterface.h"

#include "LuaStateSubsystem.h"
#include "TimerManager.h"
#include "LuaObject.h"
#include "lauxlib.h"

/*
#1 interval
#2 looping
#3 callback
*/
int LuaCppInterface::SetTimer(slua::lua_State *L)
{
	float interval = slua::LuaObject::checkValue<float>(L, 1);
	bool looping = slua::LuaObject::checkValue<bool>(L, 2);
	slua::LuaVar *func = new slua::LuaVar(L, 3, slua::LuaVar::LV_FUNCTION);

	FLuaStateSubsystem & mgr = FLuaStateSubsystem::GetLuaStateSubsystem();
	int idx = mgr.SetTimer(interval, looping, func);
	return slua::LuaObject::push(L, idx);
}

int LuaCppInterface::ClearTimer(slua::lua_State *L)
{
	int idx = slua::LuaObject::checkValue<int>(L, 1);
	FLuaStateSubsystem & mgr = FLuaStateSubsystem::GetLuaStateSubsystem();
	mgr.ClearTimer(idx);
	return 0;
}

void LuaCppInterface::create_table(slua::lua_State* L, slua::luaL_Reg* funcs)
{
	lua_newtable(L);									// t

	for (; funcs->name; ++funcs)
	{
		lua_pushstring(L, funcs->name);					// t, func_name
		lua_pushcfunction(L, funcs->func);				// t, func_name, func
		lua_rawset(L, -3);							// t
	}

	lua_setglobal(L, "CppInterface"); 
}

int LuaCppInterface::OpenLib(slua::lua_State* L)
{
	create_table(L, cppInterfaceMethods);
	return 0;
}


