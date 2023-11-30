--[[
    (PowerShell):
    
    chcp 65001
        將 console page 轉成 utf-8
]]

local umalib = require("UmaLuaLib");
local dumper = require("html_dumper");
local parser = require("event_parser");
local utility = require("utility");
local pe = require("print_enhance");
local fm = require("file_manager");
local Console = require("console");

local console = Console.new();


-- local html = GetHtmlFromUrl("https://gamewith.jp/uma-musume/article/show/302924");
-- local skill_color, skill_rare, skill_name, skill_dict = parser.getSkillData(html, "uma_skill_hyouka")

-- print(skill_color);
-- print(skill_rare);
-- print(skill_name);
-- utility.deepprint(skill_dict);
dumper.dumpArticleIdFromSiteMap();
dumper.dumpSkillBlackWhiteList(2000);
skill_data = dumper.dumpSkillData(2000);

-- utility.deepprint(skill_data);


-- dumper.dumpSkillBlackWhiteList(2500);

-- dumper.dumpArticleIdFromSiteMap();

console:close();