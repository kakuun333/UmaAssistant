--[[
    (PowerShell):
    
    chcp 65001
        將 console page 轉成 utf-8
]] local dumper = require("html_dumper");
local parser = require("event_parser");
local utility = require("utility");
local pe = require("print_enhance");
local fm = require("file_manager");
local Console = require("console");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

local console = Console.new();

-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/302924");
-- local skill_color, skill_rare, skill_name, skill_dict = parser.getSkillData(html, "uma_skill_hyouka")

dumper.dumpArticleIdFromSiteMap();
dumper.dumpSkillBlackWhiteList(2000);
dumper.dumpSkillData(2000);

-- local data = {
--     ["whitelist"] = {},
--     ["blacklist"] = {},
--     ["dumped_whitelist"] = {}
-- }
-- for i, v in ipairs(fm.getSkillWhiteList()) do data["whitelist"][i] = v; end
-- for i, v in ipairs(fm.getSkillBlackList()) do data["blacklist"][i] = v; end
-- fm.writejson(fm.SKILL_ARTICLE_ID_DATA_JSON, data);
