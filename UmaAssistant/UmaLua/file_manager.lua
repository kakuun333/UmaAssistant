local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

local fm = {};
-------------------------------------------------------------------------------------------------------

-- [ PATH ] --
-- event
fm.EVENT_BLACK_LIST_PATH = "./UmaData/event_black_list.txt";
fm.EVENT_WHITE_LIST_PATH = "./UmaData/event_white_list.txt";

-- skill
fm.SKILL_BLACK_LIST_PATH = "./UmaData/skill_black_list.txt";
fm.SKILL_WHITE_LIST_PATH = "./UmaData/skill_white_list.txt";
fm.SKILL_WHITE_LIST_FILTERED_PATH = "./UmaData/skill_white_list_filtered.txt"; -- 只包含金技能和一般技能

-- article id
local ARTICLE_ID_DATA_FOLDER = "./UmaData/article_id_data";
fm.ARTICLE_ID_JSON = ARTICLE_ID_DATA_FOLDER .. "/article_id.json";
fm.EVENT_ARTICLE_ID_DATA_JSON = ARTICLE_ID_DATA_FOLDER .. "/event_article_id_data.json";
fm.SKILL_ARTICLE_ID_DATA_JSON = ARTICLE_ID_DATA_FOLDER .. "/skill_article_id_data.json";

-- event_data
fm.EVENT_DATA_JP_JSON = "./UmaData/event_data_jp.json";

-- fm.ARTICLE_ID_PATH = "./UmaData/article_id.txt";

---@param path string
function fm.readfile(path)
    local file = io.open(path, "r");

    if file then
        local content = file:read("*a");
        file:close();

        return content;
    else
        print(string.format("無法開啟檔案: %s", path));
        return nil;
    end
end

---@param path string
---@param content string
function fm.writefile(path, content)
    local file = io.open(path, "w");

    if file then
        local content = file:write(content);
        file:close();
    else
        print("Error writing file.")
    end
end

---@param path string
---@param content string
function fm.appendfile(path, content)
    local file = io.open(path, "a");

    if file then
        local content = file:write(content);
        file:close();
    else
        print("Error appending file.")
    end
end

---@param path string
---@return table
function fm.readjson(path)
    local json_string = fm.readfile(path);
    local decode_json_data = json.decode(json_string, 1, nil);
    return decode_json_data;
end

---@param path string
---@param data table
function fm.writejson(path, data)
    local json_string = json.encode(data, {
        indent = true
    });
    fm.writefile(path, json_string);
end

function fm.getEventBlackList()
    local tmp = {};

    local file = io.open(fm.EVENT_BLACK_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do table.insert(tmp, id); end
    end

    return tmp;
end

function fm.getEventWhiteList()
    local tmp = {};

    local file = io.open(fm.EVENT_WHITE_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do table.insert(tmp, id); end
    end

    return tmp;
end

function fm.getSkillBlackList()
    local tmp = {};

    local file = io.open(fm.SKILL_BLACK_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do table.insert(tmp, id); end
    end

    return tmp;
end

function fm.getSkillWhiteList()
    local tmp = {};

    local file = io.open(fm.SKILL_WHITE_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do table.insert(tmp, id); end
    end

    return tmp;
end

function fm.getSkillWhiteListFiltered()
    local tmp = {};

    local file = io.open(fm.SKILL_WHITE_LIST_FILTERED_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do table.insert(tmp, id); end
    end

    return tmp;
end

-- function fm.getArticleId()
--     local aid_arr = {};

--     local file = io.open(fm.ARTICLE_ID_PATH, "r");
--     if file then
--         local content = file:read("*all")
--         local pattern = "<(%d+)>";
--         for id in string.gmatch(content, pattern) do table.insert(aid_arr, id); end
--     end

--     return aid_arr;
-- end

-------------------------------------------------------------------------------------------------------
return fm;
