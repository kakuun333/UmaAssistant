#include "../stdafx.h"

#include <lua.hpp>


LuaManager* LuaManager::_instance = nullptr;

bool LuaManager::_busy = false;


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





void LuaManager::DumpEventData()
{

    std::thread luaThread([=]()
        {
            ConsoleManager* consoleManager = ConsoleManager::GetInstance();
            consoleManager->Enable();

            this->SetBusy(true);

            json json_data;

            lua_State* L = luaL_newstate();
            luaL_openlibs(L);
            lua_register(L, "GetHtmlFromUrl", GetHtmlFromUrl);

            int fileState = luaL_dofile(L, global::path::std_update_event_data_lua.c_str());
            if (fileState == LUA_OK)
            {
                //lua_getglobal(L, "event_data");
                //int event_data_idx = lua_gettop(L);
                //if (lua_istable(L, event_data_idx))
                //{
                //    lua_pushnil(L);
                //    while (lua_next(L, event_data_idx) != 0)
                //    {
                //        if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1))
                //        {
                //            const char* owner_type = lua_tostring(L, -2);
                //            int owner_type_table_idx = lua_gettop(L);

                //            //std::cout << "owner_type: " << owner_type << std::endl;

                //            json_data[owner_type] = {};

                //            lua_pushnil(L);
                //            while (lua_next(L, owner_type_table_idx) != 0)
                //            {
                //                if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1))
                //                {
                //                    const char* rare = lua_tostring(L, -2);
                //                    int rare_table_idx = lua_gettop(L);

                //                    //std::cout << "rare: " << rare << std::endl;

                //                    json_data[owner_type][rare] = {};

                //                    lua_pushnil(L);
                //                    while (lua_next(L, rare_table_idx) != 0)
                //                    {
                //                        if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1))
                //                        {
                //                            const char* event_owner = lua_tostring(L, -2);
                //                            int event_owner_idx = lua_gettop(L);

                //                            //std::cout << "event_owner: " << event_owner << std::endl;

                //                            json_data[owner_type][rare][event_owner] = {};
                //                            

                //                            lua_pushnil(L);
                //                            while (lua_next(L, event_owner_idx) != 0)
                //                            {
                //                                const char* event_list = lua_tostring(L, -2);
                //                                int event_list_idx = lua_gettop(L);

                //                                json_data[owner_type][rare][event_owner][event_list] = json::array();
                //                                //std::cout << "event_list: " << event_list << std::endl;

                //                                lua_pushnil(L);
                //                                while (lua_next(L, event_list_idx) != 0)
                //                                {
                //                                    int event_lua_idx = lua_tointeger(L, -2);
                //                                    int event_idx = lua_gettop(L);

                //                                    //std::cout << "event_lua_idx: " << event_lua_idx << std::endl;

                //                                    json event_obj;

                //                                    lua_pushnil(L);
                //                                    while (lua_next(L, event_idx) != 0)
                //                                    {
                //                                        const char* event_title = lua_tostring(L, -2);
                //                                        int event_title_idx = lua_gettop(L);

                //                                        event_obj[event_title] = {};
                //                                            
                //                                        //std::cout << "event_title: " << event_title << std::endl;
                //                                        lua_pushnil(L);
                //                                        while (lua_next(L, event_title_idx) != 0)
                //                                        {
                //                                            int choice_lua_idx = lua_tointeger(L, -2);
                //                                            int choice_idx = lua_gettop(L);

                //                                            //std::cout << "-2: " << lua_type(L, -2) << std::endl;
                //                                            //std::cout << "-1: " << lua_type(L, -1) << std::endl;

                //                                            json choice_obj;

                //                                            lua_pushnil(L);
                //                                            while (lua_next(L, choice_idx) != 0)
                //                                            {
                //                                                const char* key = lua_tostring(L, -2);
                //                                                const char* value = lua_tostring(L, -1);

                //                                                if (key == "choice_title")
                //                                                {
                //                                                    choice_obj[key] = value;
                //                                                }
                //                                                else
                //                                                {
                //                                                    choice_obj[key] = value;
                //                                                }

                //                                                lua_pop(L, 1);
                //                                            }

                //                                            event_obj[event_title].push_back(choice_obj);

                //                                            lua_pop(L, 1);
                //                                        }

                //                                        json_data[owner_type][rare][event_owner][event_list].push_back(event_obj);

                //                                        lua_pop(L, 1);
                //                                    }

                //                                    lua_pop(L, 1);
                //                                }

                //                                lua_pop(L, 1);
                //                            }
                //                        }
                //                        lua_pop(L, 1);
                //                    }
                //                }
                //                lua_pop(L, 1);
                //            }
                //        }
                //        lua_pop(L, 1);
                //    }
                //}


                //std::string json_string = json_data.dump(2 /*縮排空格數*/);

                //// 寫入 json
                //std::ofstream outputFile(global::path::c_event_data_jp_json);
                //if (outputFile.is_open())
                //{
                //    outputFile << json_string << std::endl;
                //    outputFile.close();
                //    std::cout << global::path::c_event_data_jp_json << u8" 成功創建並寫入！" << std::endl;
                //}
                //else
                //{
                //    std::cerr << global::path::c_event_data_jp_json << u8" 創建失敗。" << std::endl;
                //}


            }
            else
            {
                std::string errormsg = lua_tostring(L, -1);
                std::cout << errormsg << std::endl;
            }

            lua_close(L);

            this->SetBusy(false);

            consoleManager->Disable();
        });


    luaThread.detach();
}

void LuaManager::DumpSkillData()
{

    std::thread luaThread([=]()
        {
            ConsoleManager* consoleManager = ConsoleManager::GetInstance();
            consoleManager->Enable();

            json json_data;

            lua_State* L = luaL_newstate();
            luaL_openlibs(L);
            lua_register(L, "GetHtmlFromUrl", GetHtmlFromUrl);

            int fileState = luaL_dofile(L, global::path::std_update_skill_data_lua.c_str());
            if (fileState == LUA_OK)
            {
                //lua_getglobal(L, "skill_data");
                //int skill_data_idx = lua_gettop(L);
                //if (lua_istable(L, skill_data_idx))
                //{
                //    lua_pushnil(L);
                //    while (lua_next(L, skill_data_idx) != 0)
                //    {
                //        const char* skill_color = lua_tostring(L, -2);
                //        int skill_color_idx = lua_gettop(L);

                //        json_data[skill_color] = {};

                //        lua_pushnil(L);
                //        while (lua_next(L, skill_color_idx) != 0)
                //        {
                //            const char* skill_rare = lua_tostring(L, -2);
                //            int skill_rare_idx = lua_gettop(L);

                //            json_data[skill_color][skill_rare] = {};

                //            lua_pushnil(L);
                //            while (lua_next(L, skill_rare_idx) != 0)
                //            {
                //                const char* skill_name = lua_tostring(L, -2);
                //                int skill_name_idx = lua_gettop(L);

                //                json_data[skill_color][skill_rare][skill_name] = {};

                //                lua_pushnil(L);
                //                while (lua_next(L, skill_name_idx) != 0)
                //                {
                //                    const char* key = lua_tostring(L, -2);
                //                    const char* value = lua_tostring(L, -1);

                //                    std::cout << "key: " << key << " value: " << value << std::endl;

                //                    if (strcmp(key, "skill_pt") == 0)
                //                    {
                //                        json_data[skill_color][skill_rare][skill_name][key] = value;
                //                    }
                //                    else if (strcmp(key, "skill_effect") == 0)
                //                    {
                //                        json_data[skill_color][skill_rare][skill_name][key] = value;
                //                    }
                //                    else if (strcmp(key, "upper_skill") == 0)
                //                    {
                //                        if (strcmp(value, "none") == 0)
                //                            json_data[skill_color][skill_rare][skill_name][key] = {};
                //                        else
                //                            json_data[skill_color][skill_rare][skill_name][key] = value;
                //                    }
                //                    else if (strcmp(key, "lower_skill") == 0)
                //                    {
                //                        if (strcmp(value, "none") == 0)
                //                            json_data[skill_color][skill_rare][skill_name][key] = {};
                //                        else
                //                            json_data[skill_color][skill_rare][skill_name][key] = value;
                //                    }
                //                    else if (strcmp(key, "skill_icon_name") == 0)
                //                    {
                //                        json_data[skill_color][skill_rare][skill_name][key] = value;
                //                    }


                //                    lua_pop(L, 1);
                //                }

                //                lua_pop(L, 1);
                //            }

                //            lua_pop(L, 1);
                //        }

                //        lua_pop(L, 1);
                //    }
                //}


                //std::string json_string = json_data.dump(2 /*縮排空格數*/);

                //// 寫入 json
                //std::ofstream outputFile(global::path::std_skill_data_jp_json);
                //if (outputFile.is_open())
                //{
                //    outputFile << json_string << std::endl;
                //    outputFile.close();
                //    std::cout << global::path::std_skill_data_jp_json << u8" 成功創建並寫入！" << std::endl;
                //}
                //else
                //{
                //    std::cerr << global::path::std_skill_data_jp_json << u8" 創建失敗。" << std::endl;
                //}
            }
            else
            {
                std::string errormsg = lua_tostring(L, -1);
                std::cout << errormsg << std::endl;
            }

            lua_close(L);

            consoleManager->Disable();
        });

    luaThread.detach();
}