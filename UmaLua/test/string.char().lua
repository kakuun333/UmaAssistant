--"1110" 1001,"10" 0100 01,"10" 111101
local OutOne
local OutTwo
local OutThree
function hextobin(str)
    local map = {
        ['0'] = '0000',
        ['1'] = '0001',
        ['2'] = '0010',
        ['3'] = '0011',
        ['4'] = '0100',
        ['5'] = '0101',
        ['6'] = '0110',
        ['7'] = '0111',
        ['8'] = '1000',
        ['9'] = '1001',
        ['A'] = '1010',
        ['B'] = '1011',
        ['C'] = '1100',
        ['D'] = '1101',
        ['E'] = '1110',
        ['F'] = '1111',
    }
    return str:gsub('[0-F]',map)
end

function bintodec(str)
    local MainOne = "1110"..string.sub(str,1,4)
    local MainTwo = "10"..string.sub(str,5,10)
    local MainThree = "10"..string.sub(str,11,16)
    local a
    local b
    local c
    local d
    local e
    local f
    local g
    local h
    local i
    local j
    local k
    local l
    local m
    local n
    local o
    local p
    local q
    local r
    local s
    local t
    local u
    local v
    local w
    local x
    
    
    if string.sub(MainOne,1,1) == "1" then
        a = 2 ^ 7
    else
        a = 0
    end
    
    if string.sub(MainOne,2,2) == "1" then
        b = 2 ^ 6
    else
        b = 0
    end
    
    if string.sub(MainOne,3,3) == "1" then
        c = 2 ^ 5
    else
        c = 0
    end

    if string.sub(MainOne,4,4) == "1" then
        d = 2 ^ 4
    else
        d = 0
    end
    
    if string.sub(MainOne,5,5) == "1" then
        e = 2 ^ 3
    else
        e = 0
    end
    
    if string.sub(MainOne,6,6) == "1" then
        f = 2 ^ 2
    else
        f = 0
    end
    
    if string.sub(MainOne,7,7) == "1" then
        g = 2 ^ 1
    else
        g = 0
    end

    if string.sub(MainOne,8,8) == "1" then
        h = 2 ^ 0
    else
        h = 0
    end
    --------------------------------------
    if string.sub(MainTwo,1,1) == "1" then
        i = 2 ^ 7
    else
        i = 0
    end
    
    if string.sub(MainTwo,2,2) == "1" then
        j = 2 ^ 6
    else
        j = 0
    end
    
    if string.sub(MainTwo,3,3) == "1" then
        k = 2 ^ 5
    else
        k = 0
    end

    if string.sub(MainTwo,4,4) == "1" then
        l = 2 ^ 4
    else
        l = 0
    end
    
    if string.sub(MainTwo,5,5) == "1" then
        m = 2 ^ 3
    else
        m = 0
    end

    if string.sub(MainTwo,6,6) == "1" then
        n = 2 ^ 2
    else
        n = 0
    end
    
    if string.sub(MainTwo,7,7) == "1" then
        o = 2 ^ 1
    else
        o = 0
    end

    if string.sub(MainTwo,8,8) == "1" then
        p = 2 ^ 0
    else
        p = 0
    end
    --------------------------------------
    if string.sub(MainThree,1,1) == "1" then
        q = 2 ^ 7
    else
        q = 0
    end
    
    if string.sub(MainThree,2,2) == "1" then
        r = 2 ^ 6
    else
        r = 0
    end
    
    if string.sub(MainThree,3,3) == "1" then
        s = 2 ^ 5
    else
        s = 0
    end

    if string.sub(MainThree,4,4) == "1" then
        t = 2 ^ 4
    else
        t = 0
    end
    
    if string.sub(MainThree,5,5) == "1" then
        u = 2 ^ 3
    else
        u = 0
    end
    if string.sub(MainThree,6,6) == "1" then
        v = 2 ^ 2
    else
        v = 0
    end
    
    if string.sub(MainThree,7,7) == "1" then
        w = 2 ^ 1
    else
        w = 0
    end

    if string.sub(MainThree,8,8) == "1" then
        x = 2 ^ 0
    else
        x = 0
    end
    

    

    OutOne = a+b+c+d+e+f+g+h
    OutTwo = i+j+k+l+m+n+o+p
    OutThree = q+r+s+t+u+v+w+x
    
    return OutOne,OutTwo,OutThree
end


local Unicode = "4EBA"

Unicode = hextobin(Unicode)

Unicode = bintodec(Unicode)

print("--------------")
print(OutOne..","..OutTwo..","..OutThree)
print(string.char(OutOne,OutTwo,OutThree))


