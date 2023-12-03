--[[
    (PowerShell):
    
    chcp 65001
        將 console page 轉成 utf-8

----------------------------------------------------------------
    (HTML Event Id):
        tuuzyou_a   //通常イベント(選択肢あり)
        renzoku     //連続イベント

        
        hirenzoku   //通常イベント
]]

-- package.cpath = package.cpath .. ';./?.dll'
-- local UmaLuaLib = require("UmaLuaLib")

-- local umalib = require("UmaLuaLib");
local dumper = require("html_dumper");
local parser = require("event_parser");
local utility = require("utility");
local pe = require("print_enhance");
local fm = require("file_manager");
local Console = require("console");

local console = Console.new();

--[[
    257406
    D:\Cpp\Projects\UmaAssistant\x64\Release\event_parser.lua:79: bad argument #1 to 'gsub' (string expected, got nil)    
]]
-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/257406");
-- local event_html = parser.getEventHtmlById(html, "tuuzyou_a");
-- local event_dict = parser.getEventDict(event_html);
-- utility.deepprint(event_dict);

-- skill = "弧線のプロフェッサー";

-- choice_effect = "大成功：<br><img src=\"../UmaMisc/Image/Status/speed.png\"><span class=\"status_speed\">スピード</span><span class=\"status_plus_value\">+10</span><br><img src=\"../UmaMisc/Image/Status/power.png\"><span class=\"status_power\">パワー</span><span class=\"status_plus_value\">+10</span><br>弧線のプロフェッサーのヒントLv<span class=\"status_plus_value\">+3</span><br>キタサンブラックの絆ゲージ<span class=\"status_plus_value\">+5</span><hr>成功：<br><img src=\"../UmaMisc/Image/Status/speed.png\"><span class=\"status_speed\">スピード</span><span class=\"status_plus_value\">+5</span><br><img src=\"../UmaMisc/Image/Status/power.png\"><span class=\"status_power\">パワー</span><span class=\"status_plus_value\">+5</span><br>弧線のプロフェッサーのヒントLv<span class=\"status_plus_value\">+1</span><br>キタサンブラックの絆ゲージ<span class=\"status_plus_value\">+5</span>"
-- <br>弧線のプロフェッサーのヒントLv<span class=\"status_plus_value\">+1</span>

-- choice_effect = string.gsub(choice_effect, "<br>([^<]-)のヒントLv<span class=", "<span class=\"skill_hint\">『%1』</span>のヒントLv<span class=")

-- print(choice_effect);


-- local jp_status_name_list = {
--     "スピード",
--     "スタミナ",
--     "パワー",
--     "根性",
--     "賢さ",
-- }

-- local status_class_dict = {
--     ["スピード"] = "speed",
--     ["スタミナ"] = "sutamina",
--     ["パワー"] = "power",
--     ["根性"] = "konjyou",
--     ["賢さ"] = "kasikosa",
-- }


-- choice_effect = "スタミナキープ<span class=\"status_plus_value\">+10</span>"
-- choice_effect = "スピード<span class=\"status_plus_value\">+10</span>"

-- for _, status_name in ipairs(jp_status_name_list) do
--     local replace_pattern = "<img src=\"../UmaMisc/Image/Status/"..status_class_dict[status_name]..".png\"><span class=\"status_"..status_class_dict[status_name].."\">%1</span>"
    
--     -- 避免替換到 スタミナキープ
--     choice_effect = string.gsub(choice_effect, "("..status_name..")[キープ]*", replace_pattern);
--     print(choice_effect);
-- end



dumper.dumpArticleIdFromSiteMap();
dumper.dumpEventBlackWhiteList(2000);
event_data = dumper.dumpEventData(2000);



console:close();