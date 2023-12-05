local pe = require("print_enhance");

local utility = {};

-- 打印出 table 的所有內容
function utility.deepprint(otable, keyColor, valueColor)
    keyColor = keyColor or "";
    valueColor = valueColor or "";

    if type(otable) == "table" then
        for k, v in pairs(otable) do
            if (type(v) ~= "table") then
                print(keyColor .. k .. pe.reset .. "\n" .. valueColor .. v .. pe.reset);
            else
                print(keyColor .. k .. pe.reset);
            end
            
            utility.deepprint(v, keyColor, valueColor);
        end
    end
end

-- table 深拷貝
function utility.deepcopy(otable)
    local tmp;

    if type(otable) == "table" then
        tmp = {};
        for k, v in next, otable do
            tmp[k] = utility.deepcopy(v)
        end
    else
        tmp = otable;
    end

    return tmp;
end

function utility.readfile(path)
    local file = io.open(path, "r");

    if file then
        local content = file:read("*a");
        file:close();

        return content;
    else
        print("Error opening file.")''
        return nil;
    end
end

function utility.writefile(path, str)
    local file = io.open(path, "w");

    if file then
        local content = file:write(str);
        file:close();
    else
        print("Error writing file.")''
    end
end


return utility;