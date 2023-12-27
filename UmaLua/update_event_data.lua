--[[
    (PowerShell):
    
    chcp 65001
        將 console page 轉成 utf-8

----------------------------------------------------------------
    (HTML Event Id):
        tuuzyou_a   //通常イベント(選択肢あり)
        renzoku     //連続イベント

        
        hirenzoku   //通常イベント
]] -- local UmaLuaLib = require("UmaLuaLib")
-- local umalib = require("UmaLuaLib");
local dumper = require("html_dumper");
local parser = require("event_parser");
local utility = require("utility");
local pe = require("print_enhance");
local fm = require("file_manager");
local Console = require("console");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

local console = Console.new();

--[[
    257406
    D:\Cpp\Projects\UmaAssistant\x64\Release\event_parser.lua:79: bad argument #1 to 'gsub' (string expected, got nil)    
]]
-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/266299"); -- キタサンブラック
-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/257451") -- ファインモーション
-- local event_html = parser.getEventHtmlById(html, "renzoku");
-- local event_dict = parser.getEventDict(event_html);
-- utility.writefile("./UMADAAAAAAAAAAAAAAAAA.json", json_string);

-- utility.deepprint(event_dict);

dumper.dumpArticleIdFromSiteMap();
dumper.dumpEventBlackWhiteList(2000);

dumper.dumpEventData(2000);
-- event_data = dumper.dumpEventData(2000);

-- local json_string = json.encode(event_data, {
--     indent = true
-- });

-- utility.writefile("./UmaData/event_data_jp.json", json_string);
