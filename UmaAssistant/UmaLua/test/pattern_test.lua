local status = "パワ";

local text = "これはパワーなのだ！！こりゃパワなのだ！！こりゃスピードなのだ！！"

local text2 = "こりゃパワなのだ！！"

text = string.gsub(text, status .. "[ー]?", "%0ー")
text2 = string.gsub(text2, status .. "[ー]?", "%0ー")

print("text: ", text);
print("text2: ", text2);
