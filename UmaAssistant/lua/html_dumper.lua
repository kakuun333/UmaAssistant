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

local pe = require("print_enhance");
local parser = require("event_parser");
local fm = require("file_manager")


---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 ---- 本地定數 

local DEFAULT_MILLISECONDS = 2000 --[[低於 2000 會有被拒絕訪問的風險]]

---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 

local html_id_arr = {
    "tuuzyou_a",
    "renzoku",
    "hirenzoku",
};

---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 

-- local function getBlackList()
--     local tmp = {};

--     local file = io.open("./UmaData/black_list.txt", "r");
--     if file then
--         local content = file:read("*all");
--         local pattern = "<(%d+)>";
--         for id in string.gmatch(content, pattern) do
--             table.insert(tmp, id);
--         end
--     end

--     return tmp;
-- end

-- local function getWhiteList()
--     local tmp = {};

--     local file = io.open("./UmaData/white_list.txt", "r");
--     if file then
--         local content = file:read("*all");
--         local pattern = "<(%d+)>";
--         for id in string.gmatch(content, pattern) do
--             table.insert(tmp, id);
--         end
--     end

--     return tmp;
-- end

-- local function getArticleId()
--     local aid_arr = {};

--     local file = io.open("./UmaData/article_id.txt", "r");
--     if file then
--         local content = file:read("*all")
--         local pattern = "<(%d+)>";
--         for id in string.gmatch(content, pattern) do
--             table.insert(aid_arr, id);
--         end
--     end

--     return aid_arr;
-- end

---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 

function dumper.dumpEventData(ms)
    ms = ms or DEFAULT_MILLISECONDS;

    local event_data = {--[[
        [article_id] = {
            ["event_owner"] = event_owner,
            ["event_list"] = {
                [event_1] = {
                    ["event_title"] = event_title,
                    ["choice_list"] = {
                        [choice_1] = {
                            ["choice_title"] = choice_title
                            ["choice_effect"] = choice_effect
                        },
                        [choice_2] = {
                            ["choice_title"] = choice_title
                            ["choice_effect"] = choice_effect
                        },
                    },
                } 
            },
        }
    ]]};
    
    local white_list = fm.getWhiteList();
    

    for i, white_id in ipairs(white_list) do
        local event_html = nil;
        
        local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/"..tostring(white_id));

        for i, html_id in ipairs(html_id_arr) do
            if event_html == nil then
                event_html = parser.getEventHtmlById(html, html_id);
            else
                goto continue;
            end
        end

        ::continue::
        
        local event_dict = parser.getEventDict(event_html);

        event_data[white_id] = event_dict;

        print("進度: ["..pe.red..i..pe.reset.. "/" ..pe.yellow..#white_list..pe.reset.."] "..pe.yellow..white_id..pe.reset..pe.cyan.." --"..ms.." 毫秒"..pe.reset);

        -- break; --[[ Debug 時使用 Debug 時使用 Debug 時使用 Debug 時使用 ]]
        sleep(ms);
    end

    print(pe.green.."已完成獲取資料"..pe.reset);

    return event_data;
end

function dumper.dumpBlackWhiteList(ms)
    ms = ms or DEFAULT_MILLISECONDS;

    local aid_arr = fm.getArticleId();
    -------------------------------------------------------------
    local black_list_file = io.open(fm.BLACK_LIST_PATH, "a");
    local white_list_file = io.open(fm.WHITE_LIST_PATH, "a");
    -- 如果檔案都順利開啟
    if black_list_file and white_list_file then
        local blacked_amount = 0;
        local whited_amount = 0;
        -- 獲取已儲存的黑白名單
        local saved_black_list = fm.getBlackList();
        local saved_white_list = fm.getWhiteList();
        for i, id in ipairs(aid_arr) do
            -- 跳過已儲存的黑名單
            for _, v in ipairs(saved_black_list) do
                if id == v then
                    print(pe.magenta.."跳過已儲存的黑名單："..id..pe.reset);
                    goto continue
                end;
            end
            -- 跳過已儲存的白名單
            for _, v in ipairs(saved_white_list) do
                if id == v then
                    print(pe.magenta.."跳過已儲存的白名單："..id..pe.reset);
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
                print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.red..id.."  已加入黑名單  "..pe.reset..pe.cyan..ms.." 毫秒"..pe.reset);
            else
                print("進度: " ..pe.red..i..pe.reset.. "/" ..pe.yellow..#aid_arr..pe.reset.. "   " ..pe.green..id.."  已加入白名單  "..pe.reset..pe.cyan..ms.." 毫秒"..pe.reset);
            end
            sleep(ms);
            ::continue::
        end

        black_list_file:write("\n\n黑名單總數："..blacked_amount);
        white_list_file:write("\n\n白名單總數："..whited_amount);
        black_list_file:close();
        white_list_file:close();
        print("黑白名單製作完成！");
    end
end

function dumper.dumpArticleIdFromSiteMap()
    local aid_arr = {};
    local sitemapXml = "https://gamewith.jp/uma-musume/sitemap.xml";
    local xml = GetHtmlFromUrl(sitemapXml);
    print("已獲取 xml")
    --               <loc>https://gamewith.jp/uma-musume/article/show/256047</loc>
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
        print("無法打開文件")
    end

    local file = io.open(fm.ARTICLE_ID_PATH, "w")
    if file then
        file:write("總長度："..#aid_arr.."\n\n")
        for i,v in ipairs(aid_arr) do
            file:write("<"..v..">".."\n")
        end
        file:close()
    else
        print("無法打開文件")
    end
    print("完成！");
end



-- function parser.getElementsByClassName(html, class)
--     assert(html and class, "\n[html_parser] html 或 class 是 nil。\nhtml: " .. tostring(html) .. " class: " .. tostring(class));

--     -- local pattern = "<([%w]+)[%s+].-[%s+]class=\"([^\"]+)\">(.-)</%1>";

--     -- local removed_script_html = string.gsub(html, "<script.-</script>", "")

--     local pattern = "<([%w]+)[%s+].-[%s+]class=\"(".. class .. ")\"></%1>";

--     print("pattern: " .. pattern)

--     local tag, class, content = string.match(html, pattern);
--     return tag, class, content;
-- end

-----------------------------------------------------
return dumper;