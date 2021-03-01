#include <iostream>
#include <string>

// include Lua, assumes it is local to this file
extern "C"
{
#include "lua542/include/lua.h"
#include "lua542/include/lauxlib.h"
#include "lua542/include/lualib.h"
}

// Link to lua library
#ifdef _WIN32
#pragma comment(lib, "lua542/liblua54.a")
#endif

using namespace std;

bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK) {
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;
		return false;
	}
	return true;
}

int main() {

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	if (CheckLua(L, luaL_dofile(L, "scripts/test.lua")))
	{
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			float a_in_cpp = (float)lua_tonumber(L, -1);
			cout << "a_in_cpp = " << a_in_cpp << endl;
		}
	}

	system("pause");
	lua_close(L);
	return 0;
}