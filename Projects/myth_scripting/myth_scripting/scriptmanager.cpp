
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind\luabind.hpp>
#include <myth\debug\assert.h>
#include <myth\script\scriptfunctions.h>
#include <myth\script\scriptmanager.h>

using namespace myth::script;
using namespace luabind;

ScriptManager::ScriptManager():
	m_LuaState(0)
{
	AssertExecutionCount(1,"SINGLETON ERROR: The singleton \"ScriptManager\" has been initialized more than once");
}

ScriptManager::~ScriptManager()
{
}

LUALIB_API void my_openlibs (lua_State *L);
void ScriptManager::Initialize()
{
	m_LuaState = lua_open();

	my_openlibs(m_LuaState);

	open(m_LuaState);

	module(m_LuaState)[
		def("print",(void(*)(int))print),
		def("print",(void(*)(const char*))print)
	];
}

void ScriptManager::Destroy()
{
	Assert(m_LuaState,"SCRIPTMANAGER ERROR: The scriptmanager has not been initialized, did you forget \"Initialize()\" or have you called \"Destroy()\"?");

	lua_close(m_LuaState);
	m_LuaState = 0;
}

void ScriptManager::ExecuteFile(const char* filename)
{
	Assert(m_LuaState,"SCRIPTMANAGER ERROR: The scriptmanager has not been initialized, did you forget \"Initialize()\" or have you called \"Destroy()\"?");

	int errorcode = luaL_dofile(m_LuaState,filename);
	if (errorcode != 0)
	{
		Assert(0,lua_tostring(m_LuaState,1));
		lua_pop(m_LuaState,1);
	}
}

void ScriptManager::ExecuteString(const char* str)
{
	Assert(m_LuaState,"SCRIPTMANAGER ERROR: The scriptmanager has not been initialized, did you forget \"Initialize()\" or have you called \"Destroy()\"?");

	int errorcode = luaL_dostring(m_LuaState,str);
	if (errorcode != 0)
	{
		Assert(0,lua_tostring(m_LuaState,1));
		lua_pop(m_LuaState,1);
	}
}


bool ScriptManager::GetBool(const char* globalName)
{
	PushGlobal(globalName);
	return lua_toboolean(m_LuaState,-1);
}

int ScriptManager::GetInt(const char* globalName)
{
	PushGlobal(globalName);
	return lua_tointeger(m_LuaState,-1);
}

const char* ScriptManager::GetString(const char* globalName)
{
	PushGlobal(globalName);
	return lua_tostring(m_LuaState,-1);
}

void ScriptManager::PushGlobal(const char* globalName)
{
	lua_getglobal(m_LuaState,globalName);
	if (lua_isnil(m_LuaState,-1))
	{
		Assert(0,"LUA ERROR: The variable with the specified name does not exist within LUA.");
	}
}

static const luaL_Reg lualibs[] = 
{
	{"", luaopen_base},
	{LUA_LOADLIBNAME, luaopen_package},
	{LUA_TABLIBNAME, luaopen_table},
	{LUA_STRLIBNAME, luaopen_string},
	{LUA_MATHLIBNAME, luaopen_math},
	{LUA_DBLIBNAME, luaopen_debug},
	{NULL, NULL}
};


LUALIB_API void my_openlibs (lua_State *L)
{
	const luaL_Reg *lib = lualibs;
	for (; lib->func; lib++) 
	{
		lua_pushcfunction(L, lib->func);
		lua_pushstring(L, lib->name);
		lua_call(L, 1, 0);
	}
}