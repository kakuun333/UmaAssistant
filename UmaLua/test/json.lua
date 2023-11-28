kakujson = {};

-- kakujson.__index = kakujson

-- function kakujson.new(position, driver, model)
--     local obj = {}
--     setmetatable(obj, kakujson)

--     obj.length = 0;

--     return obj;
-- end

local INDENT_COUNT = 4;


local function jsonIndent(indentCount)
    local indentStr = "";
    
    for i = 1, indentCount do
        indentStr = indentStr.." ";
    end

    return indentStr;
end



local function jsonString(string)
    string = "\""..string.."\""
    return string;
end

local function jsonGetComma(isLastValue)
    if isLastValue then
        return ",";
    else
        return "";
    end

    return "";
end

local function createObj()
    return "{\n"..jsonIndent(INDENT_COUNT * 2).."\n"..jsonIndent(INDENT_COUNT).."}";
end

local function createInnerObj()
    return "{\n"..jsonIndent(INDENT_COUNT * 2).."\n"..jsonIndent(INDENT_COUNT).."}";
end


local function deepEncodeTable(obj, objName, value)
    if type(value) == "table" then

        for k, v in pairs(value) do
            local isLastValue = false;

            if next(value, k) == nil then
                isLastValue = true;
            end

            if (type(v) ~= "table") then
                print("is not table", k, v);
            else
                print("is table", k);
                -- obj = string.gsub(obj, "%s+}", "\n"..jsonIndent(INDENT_COUNT * 2)..jsonString(k)..": "..createInnerObj()--[[ ..jsonGetComma(isLastValue) ]]);

            end
        end

        obj = deepEncodeTable(obj, k, v);
    end

    return obj;
end

local function jsonObj(objName, value, valueType, isLastValue)
    local obj;

    if valueType == "number" then
        obj = jsonIndent(INDENT_COUNT)..jsonString(objName)..": "..value..jsonGetComma(isLastValue);
    elseif valueType == "string" then
        obj = jsonIndent(INDENT_COUNT)..jsonString(objName)..": "..jsonString(value)..jsonGetComma(isLastValue);
    elseif valueType == "table" then
        obj = jsonIndent(INDENT_COUNT)..jsonString(objName)..": "..createObj()..jsonGetComma(isLastValue);

        obj = deepEncodeTable(obj, objName, value, nil)
    end
    

    return obj;
end

local function createFirstObj(k, v, valueType)
    local firstObj = "{\nFIRST_OBJ\n}"
    return string.gsub(firstObj, "(FIRST_OBJ)", jsonObj(k, v, valueType));
end

local function createNextObj(json, k, v, valueType, isLastValue)
    local nextObj = ""
    
    if not isLastValue then
        nextObj = string.gsub(json, "\n}", ",\n"..jsonObj(k, v, type(v), isLastValue).."\n}");
    end
    

    return nextObj;
end

function kakujson.encode(luatable)
    
    local tmp = "";

    local nextValueType = "";

    

    for k, v in pairs(luatable) do
        if type(k) == "string" then -- 如果是字典

            --[檢查是否為最後一個值
            local isLastValue = false;

            if next(luatable, k) == nil then
                isLastValue = true;
            end
            --檢查是否為最後一個值]

            if tmp == "" then -- 如果還沒初始化第一個　json obj
                tmp = createFirstObj(k, v, type(v));
            else
                tmp = createNextObj(tmp, k, v, type(v));

            end

        end

    end

    print(tmp);
end


return kakujson;