--[[
    讓 Lua 可以打印在 AllocConsole() 分配的控制台上

    用法：
    1. 先創建物件
    local Console = require("console");
    local console = Console.new();

    2. 再使用創建出來的 console 物件的 print() 方法打印字串
    console:print("Hellow from Lua");
    
    3. 不需要使用創建出來的 console 物件的時候使用 close() 來關閉
    console:close();
]]


console = {};
console.__index = console   

function console.new()
    local newconsole = {}
    setmetatable(newconsole, console)

    newconsole.io = io.open("CONOUT$", "w");
    io.output(newconsole.io);

    return newconsole;
end

function console:print(...)
    local args = {...};

    local tmp = {};

    for _, v in ipairs(args) do
        tostring(v);
        v = v .. "    ";
        table.insert(tmp, v);
    end

    self.io:write(table.unpack(tmp))
    self.io:write("\n")
    -- self.io:write(table.unpack(args).."\n");


    
    self.io:flush();
end

function console:close()
    self.io:close();
end



return console;