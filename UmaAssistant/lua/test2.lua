local json = require("kakujson");


local luatable = {
    ["name"] = "tanaka",
    ["age"] = 123,
    ["skill"] = {
        ["fireball"] = {
            ["time"] = 10,
            ["damage"] = 200,
        },
        ["icecream"] = {
            ["time"] = 50,
            ["damage"] = 123,
        },
    },
}

print(json.encode(luatable));
