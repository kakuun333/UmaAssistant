Settings = {
    DumpEventData = true,
    DumpSkillData = false
}
local dumper = require("html_dumper");
local parser = require("event_parser");
local util = require("util");
local pe = require("print_enhance");
local fm = require("file_manager");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

-- Dump event data
if (Settings.DumpEventData) then
    -- dumper.dumpArticleIdFromSiteMap();
    -- dumper.dumpEventBlackWhiteList(2000);
    dumper.dumpEventData(2000);
end

-- Dump skill data
if (Settings.DumpSkillData) then
    dumper.dumpArticleIdFromSiteMap();
    dumper.dumpSkillBlackWhiteList(2000);
    dumper.dumpSkillData(2000);
end
