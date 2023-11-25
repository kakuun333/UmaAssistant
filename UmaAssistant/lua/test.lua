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


local dumper = require("html_dumper");
local parser = require("event_parser");
local utility = require("utility");
local pe = require("print_enhance");
local fm = require("file_manager");


--[[
    257406
    D:\Cpp\Projects\UmaAssistant\x64\Release\event_parser.lua:79: bad argument #1 to 'gsub' (string expected, got nil)    
]]
-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/257406");
-- local event_html = parser.getEventHtmlById(html, "tuuzyou_a");
-- local event_dict = parser.getEventDict(event_html);
-- utility.deepprint(event_dict);


event_data = dumper.dumpEventData(2100);

-- dumper.dumpEventBlackWhiteList();
-- dumper.dumpSkillBlackWhiteList(2500);


-- dumper.dumpArticleIdFromSiteMap();
