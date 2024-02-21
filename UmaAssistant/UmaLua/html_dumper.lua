dumper = {};
--[[==============================================================================================================
html_dumper 的原則：公共函數一定會用到 GetHtmlFromUrl() 函數。

HTML 參考：
<div id="tuuzyou_a" class="uma_skill_table">通常イベント(選択肢あり)</div>

正規表達式：
()      ：補獲符合條件的字串內容，也就是會返回符合條件的字串
+       ：匹配多個字符
.-      ：任意字符（非貪婪）
^       ：錨點符號，匹配字符串的開頭。例如：[^)]。表示匹配開頭為 ) 的字符串
%1      ：引用第一個補獲的內容
%s      ：空白鍵
%w      ：匹配任意數字、字母（包括大小寫）。
==============================================================================================================
]]

---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 
local pe = require("print_enhance");
local parser = require("event_parser");
local fm = require("file_manager");
local Console = require("console");
local util = require("util");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 

local DEFAULT_MILLISECONDS = 2000 --[[低於 2000 會有被拒絕訪問的風險]]

---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 
local console = Console.new();

local html_id_arr = {
    "tuuzyou_a",
    "renzoku",
    "hirenzoku"
};

local LUA_DEBUG = false;

---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 

local function getDefaultEventDataTable()
    local tmp = {
        ["character"] = {
            ["3_star"] = {},
            ["2_star"] = {},
            ["1_star"] = {}
        },
        ["sapoka"] = {
            ["ssr"] = {},
            ["sr"] = {},
            ["r"] = {}
        }
    };
    return tmp;
end

local function getDefaultSkillDataTable()
    local tmp = {
        ["yellow"] = {
            ["rare"] = {},
            ["normal"] = {}
        },
        ["blue"] = {
            ["rare"] = {},
            ["normal"] = {}
        },
        ["green"] = {
            ["rare"] = {},
            ["normal"] = {}
        },
        ["red"] = {
            ["rare"] = {},
            ["normal"] = {}
        }
    }

    return tmp;
end

---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 

function dumper.dumpSkillData(ms)
    ms = ms or DEFAULT_MILLISECONDS;

    --[[
        ["yellow"] = {
            ["rare"] = {
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_description"] = skill_description,
                    ["upper_skill"] = nil,  --json == null
                    ["lower_skill"] = nil,
                    ["skill_icon_name"] = skill_icon,
                },
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_description"] = skill_description,
                    ["upper_skill"] = nil,  --json == null
                    ["lower_skill"] = nil,
                    ["skill_icon_name"] = skill_icon_name,
                },
            },
            ["normal"] = {
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_description"] = skill_description,
                    ["upper_skill"] = nil,  --json == null
                    ["lower_skill"] = nil,
                    ["skill_icon_name"] = skill_icon_name,
                },
            },
        },
        ["blue"] = {
            
        },
        ["green"] = {

        },
        ["red"] = {

        },
    ]]

    local skill_data = fm.readjson("./UmaData/skill_data_jp.json") or getDefaultSkillDataTable();

    local skill_html = nil;

    -- local white_list = fm.getSkillWhiteListFiltered();

    local skill_article_id_data = fm.readjson(fm.SKILL_ARTICLE_ID_DATA_JSON);
    local white_list = skill_article_id_data["whitelist"];

    for i, white_id in ipairs(white_list) do

        if skill_article_id_data["dumped_whitelist"] == nil then skill_article_id_data["dumped_whitelist"] = {}; end

        if skill_article_id_data["skipped_whitelist"] == nil then
            skill_article_id_data["skipped_whitelist"] = {};
        end

        for i, v in ipairs(skill_article_id_data["dumped_whitelist"]) do if v == white_id then goto continue end end

        for i, v in ipairs(skill_article_id_data["skipped_whitelist"]) do if v == white_id then goto continue end end

        local is_skip_id = false;

        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/" .. tostring(white_id));

        skill_color, skill_rare, skill_name, skill_dict = parser.getSkillData(html, "uma_skill_hyouka");

        --[[
            SkillData 不完整的原因最有可能是因為
            刻意篩選掉固有技能和進化技能
        ]]
        if skill_color == nil or skill_rare == nil or skill_name == nil or skill_dict == nil then
            console:print(pe.yellow .. "[警告] SkillData 不完整！ white_id:" .. tostring(white_id) ..
                              "\nskill_color: " .. tostring(skill_color) .. "\nskill_rare: " .. tostring(skill_rare) ..
                              "\nskill_name: " .. tostring(skill_name) .. "\nskill_dict: " .. tostring(skill_dict) ..
                              pe.reset);

            is_skip_id = true;

            goto is_skip_id_continue
        end

        if skill_dict["upper_skill"] == "none" then end

        table.insert(skill_article_id_data["dumped_whitelist"], white_id);
        fm.writejson(fm.SKILL_ARTICLE_ID_DATA_JSON, skill_article_id_data);

        console:print("white_id:", white_id, "skill_color:", skill_color, "skill_rare:", skill_rare);
        skill_data[skill_color] = skill_data[skill_color] or {}
        skill_data[skill_color][skill_rare] = skill_data[skill_color][skill_rare] or {}
        skill_data[skill_color][skill_rare][skill_name] = skill_dict;

        fm.writejson("./UmaData/skill_data_jp.json", skill_data);

        console:print("進度: [" .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #white_list .. pe.reset .. "] " ..
                          pe.yellow .. white_id .. pe.reset .. pe.cyan .. " --" .. ms .. " 毫秒" .. pe.reset);

        if LUA_DEBUG then --[[ Debug 時使用 Debug 時使用 Debug 時使用 Debug 時使用 ]] break end

        ::is_skip_id_continue::

        if (is_skip_id) then
            skill_article_id_data["skipped_whitelist"] = skill_article_id_data["skipped_whitelist"] or {};
            table.insert(skill_article_id_data["skipped_whitelist"], white_id);
            fm.writejson(fm.SKILL_ARTICLE_ID_DATA_JSON, skill_article_id_data);
        end

        sleep(ms);

        ::continue::
    end

    console:print(pe.green .. "已完成獲取 SkillData" .. pe.reset);

    return skill_data;
end

function dumper.dumpEventData(ms)
    console:print("嘗試獲取 EventData");
    ms = ms or DEFAULT_MILLISECONDS;

    --[[
    ["character"] = {
        ["3_star"] = {

        },
        ["2_star"] = {

        },
        ["1_star"] = {

        }
    },
    ["support_card"] = {
        ["SSR"] = {
            [event_owner] = {
                ["event"] = {
                    [1] =  {
                        [event_title] = {
                            [1] = {
                                ["choice_title"] = choice_title,
                                ["choice_effect"] = choice_effect
                            }
                        },
                        [event_title] = {
                            [1] = {
                                ["choice_title"] = choice_title,
                                ["choice_effect"] = choice_effect
                            }
                        }
                    },
                    [2] =  {
                        [event_title] = {
                            [1] = {
                                ["choice_title"] = choice_title,
                                ["choice_effect"] = choice_effect
                            }
                        },
                        [event_title] = {
                            [1] = {
                                ["choice_title"] = choice_title,
                                ["choice_effect"] = choice_effect
                            }
                        }
                    },
                } 
            },
        },
        ["SR"] = {

        },
        ["R"] = {

        }
    }
    ]]

    -- event_data
    local event_data_jp_json = fm.readjson(fm.EVENT_DATA_JP_JSON);
    local event_data = event_data_jp_json or getDefaultEventDataTable()

    -- event_article_id_data
    local event_article_id_data = fm.readjson(fm.EVENT_ARTICLE_ID_DATA_JSON);

    -- white_list
    local white_list = event_article_id_data["whitelist"];

    -- dumped_whitelist
    local dumped_whitelist_data = event_article_id_data["dumped_whitelist"];
    local dumped_whitelist = {};
    dumped_whitelist = dumped_whitelist_data or {};

    for i, white_id in ipairs(white_list) do
        local skip_white_id = false;

        -- 檢查是否為已抓取過的 white_id 
        for i, dumped_white_id in ipairs(dumped_whitelist_data) do
            if (white_id == dumped_white_id) then skip_white_id = true; end
        end

        if (not skip_white_id) then
            local event_html = nil;
            local owner_type = "";
            local rare = "";

            local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/" .. tostring(white_id));

            for i, html_id in ipairs(html_id_arr) do
                if event_html == nil then
                    event_html, owner_type, rare = parser.getEventHtmlById(html, html_id);
                else
                    goto continue
                end
            end

            ::continue::

            local event_dict, event_owner = parser.getEventDict(event_html);

            console:print("white_id:", white_id, "owner_type:", owner_type, "rare:", rare);
            event_data[owner_type] = event_data[owner_type] or {}
            event_data[owner_type][rare] = event_data[owner_type][rare] or {}
            event_data[owner_type][rare][event_owner] = event_dict;

            table.insert(event_article_id_data["dumped_whitelist"], white_id)

            -- 寫入 event_article_id_data.json
            fm.writejson(fm.EVENT_ARTICLE_ID_DATA_JSON, event_article_id_data)

            -- 寫入 event_data_jp.json
            fm.writejson(fm.EVENT_DATA_JP_JSON, event_data)

            console:print(
                "進度: [" .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #white_list .. pe.reset .. "] " ..
                    pe.yellow .. white_id .. pe.reset .. pe.cyan .. " --" .. ms .. " 毫秒" .. pe.reset);

            if LUA_DEBUG then break end --[[ Debug 時使用 Debug 時使用 Debug 時使用 Debug 時使用 ]]
            sleep(ms);
        else
            console:print(pe.magenta .. "已跳過抓取過的 white_id: " .. white_id .. pe.reset);
        end
    end

    console:print(pe.green .. "成功獲取 EventData ！" .. pe.reset);

    return event_data;
end

function dumper.dumpEventBlackWhiteList(ms)
    console:print("嘗試更新 Event 黑白名單");
    ms = ms or DEFAULT_MILLISECONDS;

    local article_id_list = fm.readjson(fm.ARTICLE_ID_JSON);
    -------------------------------------------------------------
    local event_article_id_data = fm.readjson(fm.EVENT_ARTICLE_ID_DATA_JSON);

    -- 獲取已儲存的黑白名單
    local saved_black_list = event_article_id_data["blacklist"];
    local saved_white_list = event_article_id_data["whitelist"];
    for i, id in ipairs(article_id_list) do
        -- 跳過已儲存的黑名單
        for _, v in ipairs(saved_black_list) do
            if id == v then
                console:print(pe.magenta .. "跳過已儲存的黑名單：" .. id .. pe.reset);
                goto continue
            end
        end
        -- 跳過已儲存的白名單
        for _, v in ipairs(saved_white_list) do
            if id == v then
                console:print(pe.magenta .. "跳過已儲存的白名單：" .. id .. pe.reset);
                goto continue
            end
        end
        -- 開始進行分析並寫入
        local blacklisted = false;
        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/" .. id);

        -- 檢查是黑名單還是白名單
        if parser.getEventHtmlById(html, html_id_arr[1]) == nil and parser.getEventHtmlById(html, html_id_arr[2]) == nil and
            parser.getEventHtmlById(html, html_id_arr[3]) == nil then

            table.insert(event_article_id_data["blacklist"], id);

            fm.writejson(fm.EVENT_ARTICLE_ID_DATA_JSON, event_article_id_data);

            blacklisted = true;
        else
            table.insert(event_article_id_data["whitelist"], id);
            fm.writejson(fm.EVENT_ARTICLE_ID_DATA_JSON, event_article_id_data);
        end

        if blacklisted then
            console:print("進度: " .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #article_id_list .. pe.reset ..
                              "   " .. pe.red .. id .. "  已加入黑名單  " .. pe.reset .. pe.cyan .. "--" .. ms ..
                              " 毫秒" .. pe.reset);
        else
            console:print("進度: " .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #article_id_list .. pe.reset ..
                              "   " .. pe.green .. id .. "  已加入白名單  " .. pe.reset .. pe.cyan .. "--" .. ms ..
                              " 毫秒" .. pe.reset);
        end
        sleep(ms);
        ::continue::
    end

    console:print(pe.green .. "Event 黑白名單製作完成！" .. pe.reset);

end

function dumper.dumpSkillBlackWhiteList(ms)
    console:print("嘗試更新 Skill 黑白名單");
    ms = ms or DEFAULT_MILLISECONDS;

    local article_id_list = fm.readjson(fm.ARTICLE_ID_JSON);
    -------------------------------------------------------------
    local skill_article_id_data = fm.readjson(fm.SKILL_ARTICLE_ID_DATA_JSON);
    local event_article_id_data = fm.readjson(fm.EVENT_ARTICLE_ID_DATA_JSON);

    -- 獲取已儲存的黑白名單
    local saved_black_list = skill_article_id_data["blacklist"]
    local saved_white_list = skill_article_id_data["whitelist"]
    local event_white_list = event_article_id_data["whitelist"]
    for i, id in ipairs(article_id_list) do

        -- 跳過已儲存的黑名單
        for _, v in ipairs(saved_black_list) do
            if id == v then
                console:print(pe.magenta .. "跳過已儲存的黑名單：" .. id .. pe.reset);
                goto continue
            end
        end

        -- 跳過已儲存的白名單
        for _, v in ipairs(saved_white_list) do
            if id == v then
                console:print(pe.magenta .. "跳過已儲存的白名單：" .. id .. pe.reset);
                goto continue
            end
        end

        -- 跳過 event 的白名單
        for _, v in ipairs(event_white_list) do
            if id == v then
                console:print(pe.magenta .. "跳過 event 的白名單：" .. id .. pe.reset);
                goto continue
            end
        end

        -- 開始進行分析並寫入
        local black_listed = false;
        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/" .. id);
        -- if not string.match(html, "<div class=\"uma_skill_hyouka\">") then
        if not string.match(html, "<h2 id=\"kouka\">") then

            table.insert(skill_article_id_data["blacklist"], id);
            fm.writejson(fm.SKILL_ARTICLE_ID_DATA_JSON, skill_article_id_data);

            black_listed = true;
        else

            table.insert(skill_article_id_data["whitelist"], id);
            fm.writejson(fm.SKILL_ARTICLE_ID_DATA_JSON, skill_article_id_data);

        end
        if black_listed then
            console:print("進度: " .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #article_id_list .. pe.reset ..
                              "   " .. pe.red .. id .. "  已加入黑名單  " .. pe.reset .. pe.cyan .. "--" .. ms ..
                              " 毫秒" .. pe.reset);
        else
            console:print("進度: " .. pe.red .. i .. pe.reset .. "/" .. pe.yellow .. #article_id_list .. pe.reset ..
                              "   " .. pe.green .. id .. "  已加入白名單  " .. pe.reset .. pe.cyan .. "--" .. ms ..
                              " 毫秒" .. pe.reset);
        end
        sleep(ms);
        ::continue::
    end

    console:print(pe.green .. "Skill 黑白名單製作完成！" .. pe.reset);
end

function dumper.dumpArticleIdFromSiteMap()
    console:print("嘗試更新 ArticleId");
    local article_id_list = {};
    local sitemapXml = "https://gamewith.jp/uma-musume/sitemap.xml";
    local xml = GetHtmlFromUrl(sitemapXml);
    console:print("已獲取 xml")
    -- <loc>https://gamewith.jp/uma-musume/article/show/256047</loc>
    local pattern = "<loc.-(%d+)</loc>";

    -- 獲取字串中的所有 article_id
    for id in string.gmatch(xml, pattern) do table.insert(article_id_list, id); end

    fm.writejson(fm.ARTICLE_ID_JSON, article_id_list);

    -- local file_idx = io.open(fm.ARTICLE_ID_INDEX_PATH, "w")
    -- if file_idx then
    --     file_idx:write("總長度：" .. #ariticle_id_list .. "\n\n")
    --     for i, v in ipairs(ariticle_id_list) do file_idx:write(tostring(i) .. ": " .. v .. "\n") end
    --     file_idx:close()
    -- else
    --     console:print("無法打開文件")
    -- end

    -- local file = io.open(fm.ARTICLE_ID_PATH, "w")
    -- if file then
    --     file:write("總長度：" .. #ariticle_id_list .. "\n\n")
    --     for i, v in ipairs(ariticle_id_list) do file:write("<" .. v .. ">" .. "\n") end
    --     file:close()
    -- else
    --     console:print("無法打開文件")
    -- end

    console:print(pe.green .. "ArticleId 更新完成！" .. pe.reset);
end

-----------------------------------------------------
return dumper;
