local pe = {
    reset           = "\27[0m",
    bold            = "\27[1m",
    blur            = "\27[2m", -- does not works in some terminals. 不是所有終端機都有效果。

    underscore      = "\27[4m",
    us              = "\27[4m",
    
    strikethrough   = "\27[9m",
    st              = "\27[9m",

    black           = "\27[30m",
    red             = "\27[31m",
    green           = "\27[32m",
    yellow          = "\27[33m",
    blue            = "\27[34m",
    magenta         = "\27[35m", -- 紫色
    cyan            = "\27[36m", -- 青色
    white           = "\27[37m",

    -- background
    _black           = "\27[40m",
    _red             = "\27[41m",
    _green           = "\27[42m",
    _yellow          = "\27[43m",
    _blue            = "\27[44m",
    _magenta         = "\27[45m", -- 紫色
    _cyan            = "\27[46m", -- 青色
    _white           = "\27[47m",
};



return pe;