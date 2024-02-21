local pe = require("print_enhance");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

local util = {};

-- 打印出 table 的所有內容
function util.deepprint(otable, keyColor, valueColor)
    keyColor = keyColor or "";
    valueColor = valueColor or "";

    if type(otable) == "table" then
        for k, v in pairs(otable) do
            if (type(v) ~= "table") then
                print(keyColor .. k .. pe.reset .. "\n" .. valueColor .. v .. pe.reset);
            else
                print(keyColor .. k .. pe.reset);
            end

            util.deepprint(v, keyColor, valueColor);
        end
    end
end

-- table 深拷貝
function util.deepcopy(otable)
    local tmp;

    if type(otable) == "table" then
        tmp = {};
        for k, v in next, otable do tmp[k] = util.deepcopy(v) end
    else
        tmp = otable;
    end

    return tmp;
end

return util;
