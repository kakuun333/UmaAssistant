local pe = require("print_enhance");

local utility = {};

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


return utility;