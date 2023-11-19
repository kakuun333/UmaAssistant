local fm = {};
-------------------------------------------------------------------------------------------------------

-- PATH
BLACK_LIST_PATH = "./UmaData/black_list.txt";
WHITE_LIST_PATH = "./UmaData/white_list.txt";
ARTICLE_ID_PATH = "./UmaData/article_id.txt";
ARTICLE_ID_INDEX_PATH = "./UmaData/article_id_index.txt";

function fm.getBlackList()
    local tmp = {};

    local file = io.open(BLACK_LIST_PATH, "r");
    if file then
        local content = file:read("*all");
        local pattern = "<(%d+)>";
        for id in string.gmatch(content, pattern) do
            table.insert(tmp, id);
        end
    end

    return tmp;
end

function fm.getWhiteList()
    local tmp = {};

    local file = io.open(WHITE_LIST_PATH, "r");
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

    local file = io.open(ARTICLE_ID_PATH, "r");
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