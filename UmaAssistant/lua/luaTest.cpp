#include "../stdafx.h"

#include <lua.hpp>


// 回調函數，用於處理接收到的數據
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int sleep(lua_State* L)
{
    int ms = luaL_checkinteger(L, 1);


    std::this_thread::sleep_for(std::chrono::milliseconds(ms));


    return 0;
}

int GetHtmlFromUrl(lua_State* L)
{
    const char* url = luaL_checkstring(L, 1);

    CURL* curl;
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





void testlua()
{

    std::thread luaThread([=]()
        {
            json json_data;

            lua_State* L = luaL_newstate();
            luaL_openlibs(L);
            lua_register(L, "sleep", sleep);
            lua_register(L, "GetHtmlFromUrl", GetHtmlFromUrl);

            int r = luaL_dofile(L, utility::CombineChar(global::path::c_currentDir, "\\UmaAssistant\\lua\\test.lua"));
            if (r == LUA_OK)
            {
                lua_getglobal(L, "event_data");
                int event_data_idx = lua_gettop(L);
                if (lua_istable(L, event_data_idx))
                {
                    lua_pushnil(L);
                    while (lua_next(L, event_data_idx) != 0)
                    {
                        int article_id = lua_tointeger(L, -2);
                        int table_idx_1 = lua_gettop(L);

                        //std::cout << article_id << std::endl;
                        std::string article_id_str = std::to_string(article_id);
                        json_data[article_id_str] = {};

                        lua_pushnil(L);
                        while (lua_next(L, table_idx_1) != 0)
                        {
                            const char* article_id_key = lua_tostring(L, -2);
                            int table_idx_2 = lua_gettop(L);


                            if (strcmp(article_id_key, "event_owner") == 0)
                            {
                                const char* event_owner = lua_tostring(L, -1);
                                //std::cout << event_owner << std::endl;
                                json_data[article_id_str][article_id_key] = event_owner;
                            }
                            else // article_id_key == event_list
                            {
                                const char* event_list = lua_tostring(L, -2);

                                lua_pushnil(L);
                                while (lua_next(L, table_idx_2) != 0)
                                {
                                    const char* event = lua_tostring(L, -2);
                                    int table_idx_3 = lua_gettop(L);

                                    json_data[article_id_str][event_list][event] = {};
                                    //std::cout << slot << std::endl;

                                    lua_pushnil(L);
                                    while (lua_next(L, table_idx_3) != 0)
                                    {
                                        int key_type = lua_type(L, -2);
                                        if (key_type == LUA_TSTRING) // 不知道為什麼會跑出 LUA_TBOOLEAN，所以用 lua_type() 篩選成 LUA_TSTRING
                                        {
                                            const char* event_key = lua_tostring(L, -2);

                                            if (strcmp(event_key, "event_title") == 0)
                                            {
                                                const char* event_title = lua_tostring(L, -1);
                                                //std::cout << event_title << std::endl;
                                                json_data[article_id_str][event_list][event][event_key] = event_title;
                                            }
                                            else // event_key == choice_list
                                            {
                                                const char* choice_list = lua_tostring(L, -2);

                                                int table_idx_4 = lua_gettop(L);

                                                lua_pushnil(L);
                                                while (lua_next(L, table_idx_4) != 0)
                                                {
                                                    const char* choice = lua_tostring(L, -2);
                                                    int table_idx_5 = lua_gettop(L);

                                                    json_data[article_id_str][event_list][event][choice_list][choice] = {};

                                                    lua_pushnil(L);
                                                    while (lua_next(L, table_idx_5) != 0)
                                                    {
                                                        const char* key = lua_tostring(L, -2);
                                                        const char* value = lua_tostring(L, -1);

                                                        json_data[article_id_str][event_list][event][choice_list][choice][key] = value;

                                                        lua_pop(L, 1);
                                                    }

                                                    lua_pop(L, 1);
                                                }
                                            }
                                        }
                                        lua_pop(L, 1);
                                    }

                                    lua_pop(L, 1);
                                }
                            }
                            lua_pop(L, 1);
                        }
                        lua_pop(L, 1);
                    }
                }


                std::string json_string = json_data.dump(4 /*縮排空格數*/);

                // 寫入 json
                std::ofstream outputFile(global::path::event_data_jp_json);
                if (outputFile.is_open())
                {
                    outputFile << json_string << std::endl;
                    outputFile.close();
                    std::cout << u8"event_data.json 成功創建並寫入！" << std::endl;
                }
                else
                {
                    std::cerr << u8"event_data.json 創建失敗。" << std::endl;
                }
            }
            else
            {
                std::string errormsg = lua_tostring(L, -1);
                std::cout << errormsg << std::endl;
            }

            lua_close(L);
        });


    luaThread.detach();
}