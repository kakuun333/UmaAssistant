/*

compile cmd:

g++ -shared -o UmaLuaLib.dll UmaLuaLib.cpp -ID:/Cpp/Projects/UmaAssistant/vcpkg/installed/x64-windows/include -I"D:/Program Files/Lua/lua54/include" -LD:/Cpp/Projects/UmaAssistant/vcpkg/installed/x64-windows/lib -L"D:/Program Files/Lua/lua54/lib" -lcurl -llua54

*/

#include <iostream>
#include <thread>

#include <curl/curl.h>

#include <lua.hpp>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}


static int l_sleep(lua_State* L)
{
    int ms = luaL_checkinteger(L, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return 0;
}

static int l_GetHtmlFromUrl(lua_State *L)
{
    const char *url = luaL_checkstring(L, 1);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT); // 初始化 libcurl

    curl = curl_easy_init(); // 創建一個 CURL 句柄

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url); // 設置 url

        // 設置回調函數
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl); // 請求 HTTP

        // 檢查請求結果
        if (res == CURLE_OK)
        {
            lua_pushstring(L, response.c_str()); // 返回 html 給調用這個函數的 lua 變數
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl); // 清理 CURL 句柄
    }

    curl_global_cleanup(); // 清理 libcurl

    return 1; /* 返回的值的數量 */
}

static struct luaL_Reg UmaLib[] =
{
    {"sleep", l_sleep},
    {"GetHtmlFromUrl", l_GetHtmlFromUrl},
    {NULL, NULL} /* sentinel */
};

extern "C" int luaopen_UmaLuaLib(lua_State * L)
{
    luaL_newlib(L, UmaLib);
    return 1;
}