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
==============================================================================================================]]
dumper = {};

---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 ---- 引用 

local umalib = require("UmaLuaLib");
local pe = require("print_enhance");
local parser = require("event_parser");
local fm = require("file_manager");
local Console = require("console");







---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 

local DEFAULT_MILLISECONDS = 2000 --[[低於 2000 會有被拒絕訪問的風險]]

---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 
local console = Console.new();

local html_id_arr = {
    "tuuzyou_a",
    "renzoku",
    "hirenzoku",
};

local LUA_DEBUG = false;

---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 

function dumper.dumpSkillData(ms)
    ms = ms or DEFAULT_MILLISECONDS;

    local skill_data = {--[[
        ["yellow"] = {
            ["rare"] = {
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_effect"] = skill_effect,
                    ["upper_skill"] = nil,  --json == null
                    ["lower_skill"] = nil,
                    ["skill_icon_name"] = skill_icon,
                },
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_effect"] = skill_effect,
                    ["upper_skill"] = nil,  --json == null
                    ["lower_skill"] = nil,
                    ["skill_icon_name"] = skill_icon_name,
                },
            },
            ["normal"] = {
                [skill_name] = {
                    ["skill_pt"] = skill_pt,
                    ["skill_effect"] = skill_effect,
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
    ]]}

    local skill_html = nil;

    local white_list = fm.getSkillWhiteListFiltered();


    for i, white_id in ipairs(white_list) do
        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/"..tostring(white_id));

        skill_color, skill_rare, skill_name, skill_dict = parser.getSkillData(html, "uma_skill_hyouka");

        --[[
            SkillData 不完整的原因最有可能是因為
            刻意篩選到固有技能和進化技能
        ]]
        if skill_color == nil or skill_rare == nil or skill_name == nil or skill_dict == nil then
            console:print(pe.yellow.."[警告] SkillData 不完整！ white_id:" ..tostring(white_id).."\nskill_color: "..tostring(skill_color).."\nskill_rare: "..tostring(skill_rare).."\nskill_name: "..tostring(skill_name).."\nskill_dict: "..tostring(skill_dict)..pe.reset)
            goto continue
        end

        console:print("white_id:", white_id, "skill_color:", skill_color, "skill_rare:", skill_rare);
        skill_data[skill_color] = skill_data[skill_color] or {}
        skill_data[skill_color][skill_rare] = skill_data[skill_color][skill_rare] or {}
        skill_data[skill_color][skill_rare][skill_name] = skill_dict;

        console:print("進度: ["..pe.red..i..pe.reset.. "/" ..pe.yellow..#white_list..pe.reset.."] "..pe.yellow..white_id..pe.reset..pe.cyan.." --"..ms.." 毫秒"..pe.reset);

        if LUA_DEBUG then --[[ Debug 時使用 Debug 時使用 Debug 時使用 Debug 時使用 ]]
            break;
        end

        ::continue::
        umalib.sleep(ms);
    end

    console:print(pe.green.."已完成獲取 SkillData"..pe.reset);

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

    local event_data = {
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
                
            },
            ["SR"] = {

            },
            ["R"] = {

            }
        }
    };
    
    local white_list = fm.getEventWhiteList();
    

    for i, white_id in ipairs(white_list) do
        local event_html = nil;
        local owner_type = "";
        local rare = "";
        
        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/"..tostring(white_id));

        for i, html_id in ipairs(html_id_arr) do
            if event_html == nil then
                event_html, owner_type, rare = parser.getEventHtmlById(html, html_id);
            else
                goto continue;
            end
        end

        ::continue::
        
        local event_dict, event_owner = parser.getEventDict(event_html);

        console:print("white_id:", white_id, "owner_type:", owner_type, "rare:", rare);
        event_data[owner_type] = event_data[owner_type] or {}
        event_data[owner_type][rare] = event_data[owner_type][rare] or {}
        event_data[owner_type][rare][event_owner] = event_dict;

        console:print("進度: ["..pe.red..i..pe.reset.. "/" ..pe.yellow..#white_list..pe.reset.."] "..pe.yellow..white_id..pe.reset..pe.cyan.." --"..ms.." 毫秒"..pe.reset);

        if LUA_DEBUG then --[[ Debug 時使用 Debug 時使用 Debug 時使用 Debug 時使用 ]]
            break;
        end
        umalib.sleep(ms);
    end

    console:print(pe.green.."成功獲取 EventData ！"..pe.reset);

    return event_data;
end

function dumper.dumpEventBlackWhiteList(ms)
    console:print("嘗試更新 Event 黑白名單");
    ms = ms or DEFAULT_MILLISECONDS;

    local aid_arr = fm.getArticleId();
    -------------------------------------------------------------
    local black_list_file = io.open(fm.EVENT_BLACK_LIST_PATH, "a");
    local white_list_file = io.open(fm.EVENT_WHITE_LIST_PATH, "a");
    -- 如果檔案都順利開啟
    if black_list_file and white_list_file then
        local blacked_amount = 0;
        local whited_amount = 0;
        -- 獲取已儲存的黑白名單
        local saved_black_list = fm.getEventBlackList();
        local saved_white_list = fm.getEventWhiteList();
        for i, id in ipairs(aid_arr) do
            -- 跳過已儲存的黑名單
            for _, v in ipairs(saved_black_list) do
                if id == v then
                    console:print(pe.magenta.."跳過已儲存的黑名單："..id..pe.reset);
                    goto continue
                end;
            end
            -- 跳過已儲存的白名單
            for _, v in ipairs(saved_white_list) do
                if id == v then
                    console:print(pe.magenta.."跳過已儲存的白名單："..id..pe.reset);
                    goto continue
                end;
            end
            -- 開始進行分析並寫入
            local black_listed = false;
            local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/"..id);
            if parser.getEventHtmlById(html, html_id_arr[1]) == nil and
            parser.getEventHtmlById(html, html_id_arr[2]) == nil and
            parser.getEventHtmlById(html, html_id_arr[3]) == nil then
                black_list_file:write("<"..id..">".."\n");
                black_list_file:flush();
                blacked_amount = blacked_amount + 1;
                black_listed = true;
            else
                whited_amount = whited_amount  + 1;
                white_list_file:write("<"..id..">".."\n");
                white_list_file:flush();
            end
            if black_listed then
                console:print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.red..id.."  已加入黑名單  "..pe.reset..pe.cyan.."--"..ms.." 毫秒"..pe.reset);
            else
                console:print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.green..id.."  已加入白名單  "..pe.reset..pe.cyan.."--"..ms.." 毫秒"..pe.reset);
            end
            umalib.sleep(ms);
            ::continue::
        end

        -- black_list_file:write("\n\n黑名單總數："..blacked_amount);
        -- white_list_file:write("\n\n白名單總數："..whited_amount);
        black_list_file:close();
        white_list_file:close();
        console:print(pe.green.."Event 黑白名單製作完成！"..pe.reset);
    end
end

function dumper.dumpSkillBlackWhiteList(ms)
    console:print("嘗試更新 Skill 黑白名單");
    ms = ms or DEFAULT_MILLISECONDS;

    local aid_arr = fm.getArticleId();
    -------------------------------------------------------------
    local black_list_file = io.open(fm.SKILL_BLACK_LIST_PATH, "a");
    local white_list_file = io.open(fm.SKILL_WHITE_LIST_PATH, "a");
    -- 如果檔案都順利開啟
    if black_list_file and white_list_file then
        local blacked_amount = 0;
        local whited_amount = 0;
        -- 獲取已儲存的黑白名單
        local saved_black_list = fm.getSkillBlackList();
        local saved_white_list = fm.getSkillWhiteList();
        local event_white_list = fm.getEventWhiteList();
        for i, id in ipairs(aid_arr) do
            -- 跳過已儲存的黑名單
            for _, v in ipairs(saved_black_list) do
                if id == v then
                    console:print(pe.magenta.."跳過已儲存的黑名單："..id..pe.reset);
                    goto continue
                end;
            end
            -- 跳過已儲存的白名單
            for _, v in ipairs(saved_white_list) do
                if id == v then
                    console:print(pe.magenta.."跳過已儲存的白名單："..id..pe.reset);
                    goto continue
                end;
            end
            -- 跳過 event 的白名單
            
            for _, v in ipairs(event_white_list) do
                if id == v then
                    console:print(pe.magenta.."跳過 event 的白名單："..id..pe.reset);
                    goto continue
                end;
            end

            -- 開始進行分析並寫入
            local black_listed = false;
            local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/"..id);
            if not string.match(html, "<div class=\"uma_skill_hyouka\">") then
                black_list_file:write("<"..id..">".."\n");
                black_list_file:flush();
                blacked_amount = blacked_amount + 1;
                black_listed = true;
            else
                whited_amount = whited_amount  + 1;
                white_list_file:write("<"..id..">".."\n");
                white_list_file:flush();
            end
            if black_listed then
                console:print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.red..id.."  已加入黑名單  "..pe.reset..pe.cyan.."--"..ms.." 毫秒"..pe.reset);
            else
                console:print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.green..id.."  已加入白名單  "..pe.reset..pe.cyan.."--"..ms.." 毫秒"..pe.reset);
            end
            umalib.sleep(ms);
            ::continue::
        end

        -- black_list_file:write("\n\n黑名單總數："..blacked_amount);
        -- white_list_file:write("\n\n白名單總數："..whited_amount);
        black_list_file:close();
        white_list_file:close();
        console:print(pe.green.."Skill 黑白名單製作完成！"..pe.reset);
    end
end

function dumper.dumpArticleIdFromSiteMap()
    console:print("嘗試更新 ArticleId");
    local aid_arr = {};
    local sitemapXml = "https://gamewith.jp/uma-musume/sitemap.xml";
    local xml = GetHtmlFromUrl(sitemapXml);
    console:print("已獲取 xml")
    -- <loc>https://gamewith.jp/uma-musume/article/show/256047</loc>
    local pattern = "<loc.-(%d+)</loc>";
    for id in string.gmatch(xml, pattern) do
        -- print(id.."\n")
        table.insert(aid_arr, id);
    end

    local file_idx = io.open(fm.ARTICLE_ID_INDEX_PATH, "w")
    if file_idx then
        file_idx:write("總長度："..#aid_arr.."\n\n")
        for i,v in ipairs(aid_arr) do
            file_idx:write(tostring(i)..": "..v.."\n")
        end
        file_idx:close()
    else
        console:print("無法打開文件")
    end

    local file = io.open(fm.ARTICLE_ID_PATH, "w")
    if file then
        file:write("總長度："..#aid_arr.."\n\n")
        for i,v in ipairs(aid_arr) do
            file:write("<"..v..">".."\n")
        end
        file:close()
    else
        console:print("無法打開文件")
    end
    console:print(pe.green.."ArticleId 更新完成！"..pe.reset);
end



-- function parser.getElementsByClassName(html, class)
--     assert(html and class, "\n[html_parser] html 或 class 是 nil。\nhtml: " .. tostring(html) .. " class: " .. tostring(class));

--     -- local pattern = "<([%w]+)[%s+].-[%s+]class=\"([^\"]+)\">(.-)</%1>";

--     -- local removed_script_html = string.gsub(html, "<script.-</script>", "")

--     local pattern = "<([%w]+)[%s+].-[%s+]class=\"(".. class .. ")\"></%1>";

--     console:print("pattern: " .. pattern)

--     local tag, class, content = string.match(html, pattern);
--     return tag, class, content;
-- end

-----------------------------------------------------
return dumper;