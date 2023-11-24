local fm = {};
-------------------------------------------------------------------------------------------------------

-- [ PATH ] --
-- event
fm.EVENT_BLACK_LIST_PATH = "./UmaData/event_black_list.txt";
fm.EVENT_WHITE_LIST_PATH = "./UmaData/event_white_list.txt";

-- skill
fm.SKILL_BLACK_LIST_PATH = "./UmaData/skill_black_list.txt";
fm.SKILL_WHITE_LIST_PATH = "./UmaData/skill_white_list.txt";

-- article id
fm.ARTICLE_ID_PATH = "./UmaData/article_id.txt";
fm.ARTICLE_ID_INDEX_PATH = "./UmaData/article_id_index.txt";

function fm.getEventBlackList()
    local tmp = {};

    local file = io.open(fm.EVENT_BLACK_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(tmp, id);
        end
    end

    return tmp;
end

function fm.getEventWhiteList()
    local tmp = {};

    local file = io.open(fm.EVENT_WHITE_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(tmp, id);
        end
    end

    return tmp;
end

function fm.getSkillBlackList()
    local tmp = {};

    local file = io.open(fm.SKILL_BLACK_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(tmp, id);
        end
    end

    return tmp;
end

function fm.getSkillWhiteList()
    local tmp = {};

    local file = io.open(fm.SKILL_WHITE_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(tmp, id);
        end
    end

    return tmp;
end

function fm.getArticleId()
    local aid_arr = {};

    local file = io.open(fm.ARTICLE_ID_PATH, "r");
    if file then
        local content = file:read("*all")
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(aid_arr, id);
        end
    end

    return aid_arr;
end

-------------------------------------------------------------------------------------------------------
return fm;