/*

compile cmd:

g++ -shared -o umalib.dll umalib.cpp -ID:/Cpp/Projects/UmaAssistant/vcpkg/installed/x64-windows/include -I"D:/Program Files/Lua/lua54/include" -LD:/Cpp/Projects/UmaAssistant/vcpkg/installed/x64-windows/lib -L"D:/Program Files/Lua/lua54/lib" -lcurl -llua54

*/

#include <lua.hpp>

int test_add1(lua_State *L)
{
    double d = luaL_checknumber(L, 1); // get item 1
    lua_pushnumber(L, d + 1);
    return 1; // number of items returned
}
static const struct luaL_reg testlib[] =
    {
        {"add1", test_add1},
        {NULL, NULL}};
extern "C" int luaopen_test(lua_State *L)
{
    lua_register(L, "test", testlib);
    return 1;
}