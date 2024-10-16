local pe = require("print_enhance");
local fm = require("file_manager");
local util = require("util");
local Console = require("console");
local json = require("dkjson"); -- http://dkolf.de/src/dkjson-lua.fsl/home

parser = {}

---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 ---- 本地變數 
local console = Console.new();

---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 ---- 本地函數 
local function fixWrongSkillName(choice_effect)
    local wrong_word_data = fm.readjson("./UmaData/wrong_word_data.json");

    for wrong_skill, correct_skill in pairs(wrong_word_data["skill_name_list"]) do
        if string.match(choice_effect, wrong_skill) then
            choice_effect = string.gsub(choice_effect, wrong_skill, correct_skill);
        end
    end

    return choice_effect
end

---@param input string
local function fixWrongStatusName(input)

    input = string.gsub(input, "(パワ)(ー)?", "%1ー")

    return input;
end

local function placeTagToStatus(choice_effect)
    local html_tag_data = fm.readjson("./UmaData/html_tag_data.json");

    -- 給 choice_effect 相對應的 status 添加 <img> 和 <span>
    for _, status_name in pairs(html_tag_data["jp_status_name_list"]) do
        local replace_pattern =
            "<img src=\"../UmaMisc/Image/Status/" .. html_tag_data["status_class_dict"][status_name] ..
                ".png\"><span class=\"status_" .. html_tag_data["status_class_dict"][status_name] .. "\">%1</span>"

        choice_effect = string.gsub(choice_effect, "(" .. status_name .. ")", replace_pattern);
        -- 『<img src=\"../UmaMisc/Image/Status/speed.png\"><span class=\"status_speed\">スピード</span>スター』
        choice_effect = string.gsub(choice_effect,
            "『<img src=\"../UmaMisc/Image/Status/" .. html_tag_data["status_class_dict"][status_name] ..
                ".png\"><span class=\"status_" .. html_tag_data["status_class_dict"][status_name] .. "\">" ..
                status_name .. "</span>(.-)』", "『" .. status_name .. "%1』");
    end

    -- 負號
    choice_effect = string.gsub(choice_effect, "－(%d+)", "-%1");
    -- choice_effect = string.gsub(choice_effect, "([%-%d]+~%d+)", "<span class=\"status_minus_value\">%1</span>");
    choice_effect = string.gsub(choice_effect, "(%-%d+[~%d+]*)", "<span class=\"status_minus_value\">%1</span>");

    -- 正號
    choice_effect = string.gsub(choice_effect, "＋(%d+)", "+%1");
    -- choice_effect = string.gsub(choice_effect, "([%+%d]+~%d+)", "<span class=\"status_plus_value\">%1</span>");
    choice_effect = string.gsub(choice_effect, "(%+%d+[~%d+]*)", "<span class=\"status_plus_value\">%1</span>");

    -- choice_effect = string.gsub(choice_effect, "?!>([%+%d+]+~?%d*)?!<", "<span class=\"status_plus_value\">%1</span>");

    return choice_effect;
end

local function placeTagToSkillHint(choice_effect)
    --[[
    例外狀況：
    『バ場状況や出場したレース場に関係するスキルのヒント』
    ]]

    local content = fm.readfile("./UmaData/wrong_word_data.json");
    local wrong_word_data, pos, err = json.decode(content, 1, nil)

    local content = fm.readfile("./UmaData/condition_data.json");
    local condition_data, pos, err = json.decode(content, 1, nil)

    for skillOrCondition in string.gmatch(choice_effect, "『(.-)』") do
        for _, condition in pairs(condition_data["all_condition_list"]) do
            if skillOrCondition == condition or skillOrCondition ==
                "バ場状況や出場したレース場に関係するスキルのヒント" then
                goto continue
            end
        end

        local skill = skillOrCondition
        for wrong_skill, correct_skill in pairs(wrong_word_data["skill_name_list"]) do
            if (skill == wrong_skill) then skill = correct_skill; end
        end

        -- console:print(skill);

        choice_effect = string.gsub(choice_effect, "『" .. skill .. "』",
            "<span class=\"skill_hint\">『" .. skill .. "』</span>")

        --[[
            錯字：孤線->弧線
            <span class=\"status_plus_value\">+10</span><br>孤線のプロフェッサーのヒントLv<span class=\"status_plus_value\">+3</span><br>
        ]]

        ::continue::
    end

    --[[
        因為有些技能沒有加上『』，所以特別再檢查一次
    ]]
    choice_effect = string.gsub(choice_effect, "<br>([^<]-)のヒントLv<span class=",
        "<span class=\"skill_hint\">『%1』</span>のヒントLv<span class=");

    return choice_effect;
end

local function placeTagToCondition(choice_effect)
    local content = fm.readfile("./UmaData/condition_data.json");
    local condition_data, pos, err = json.decode(content, 1, nil)

    for skillOrCondition in string.gmatch(choice_effect, "『(.-)』") do
        for _, plus_condition in pairs(condition_data["plus_condition_list"]) do
            if skillOrCondition == plus_condition then
                local plus_condition = skillOrCondition
                -- console:print(plus_condition)
                choice_effect = string.gsub(choice_effect, "『" .. plus_condition .. "』",
                    "<span class=\"plus_condition\">『" .. plus_condition .. "』</span>")
            end
        end
    end

    for skillOrCondition in string.gmatch(choice_effect, "『(.-)』") do
        for _, minus_condition in pairs(condition_data["minus_condition_list"]) do
            if skillOrCondition == minus_condition then
                local minus_condition = skillOrCondition
                -- console:print(minus_condition)
                choice_effect = string.gsub(choice_effect, "『" .. minus_condition .. "』",
                    "<span class=\"minus_condition\">『" .. minus_condition .. "』</span>")
            end
        end
    end

    return choice_effect;
end

---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 ---- 公共函數 

function parser.getSkillData(html, class)
    assert(html and class,
        "\n[html_parser] html 或 class 是 nil。\n" .. "html: " .. tostring(html) .. " class: " .. tostring(class));

    -- 技能稀有度
    local skill_rare = nil;

    if string.match(html, "<th>種類.-ノーマル</td>") ~= nil then skill_rare = "normal" end
    if string.match(html, "<th>種類.-レア</td>") ~= nil then skill_rare = "rare" end
    if skill_rare == nil then return nil, nil, nil, nil end

    -- 技能顏色
    local skill_color = nil;
    local skill_type_pattern = "<h2 id=\"kouka\">.-<img.-i_skill_(.-)_(.-)_(%d+).->"
    local color, rare, number = string.match(html, skill_type_pattern);

    if color == "y" then
        skill_color = "yellow";
    elseif color == "b" then
        skill_color = "blue";
    elseif color == "g" then
        skill_color = "green";
    elseif color == "r" then
        skill_color = "red";
    end

    -- 技能縮圖
    local skill_icon_name = nil;
    local skill_icon_pattern = "<h2 id=\"kouka\">.-<img.-(i_skill_.-)%..->"
    skill_icon_name = string.match(html, skill_icon_pattern);

    -- 技能名稱
    local skill_name_pattern = "<h1 class=\"_title\">【ウマ娘】「(.-)」";
    local skill_name = string.match(html, skill_name_pattern);
    skill_name = string.gsub(skill_name, "%(丸%)", "");
    skill_name = string.gsub(skill_name, "%(二重丸%)", "");

    skill_name = string.gsub(skill_name, "○", "◯");
    skill_name = string.gsub(skill_name, "〇", "◯");

    -- 初始化 skill_dict
    local skill_dict = { --[[
        [skill_name] = {
            ["skill_pt"] = skill_pt,
            ["skill_description"] = skill_description,
            ["upper_skill"] = nil,  --json == null
            ["lower_skill"] = nil,
            ["skill_icon_name"] = skill_icon_name,
        }
    ]]
    }

    -- 獲取 skill_html
    local body_pattern = "<body>(.-)</body>";
    local skill_html = string.match(html, body_pattern);

    local skill_pt = string.match(skill_html, "<th>必要Pt.-<td>(%d+)</td>") or json.null;

    --------------------------[修正]--------------------------
    -- ライトニングステップ 的圖示名稱有錯誤，所以特別修正
    if (skill_name == "ライトニングステップ") then skill_icon_name = "i_skill_y_r_3"; end

    -- 修正缺少技能點的技能
    if (skill_name == "コール＆レスポンス") then skill_pt = "200"; end
    if (skill_name == "二段構え") then skill_pt = "200"; end

    -- skill_description
    local skill_description = string.match(skill_html, "<th>効果.-<td>(.-)</td>") or json.null;

    -- upper_skill
    local upper_skill = json.null;
    local lower_skill = json.null;

    if skill_rare == "normal" then
        if string.match(skill_html, "<th>上位スキル.-<td>なし</td>") then goto continue_skill_dict end
        upper_skill = string.match(skill_html, "<th>上位スキル.-<td><a.->(.-)</a>") or json.null;
    elseif skill_rare == "rare" then
        if string.match(skill_html, "<th>下位スキル.-<td>なし</td>") then goto continue_skill_dict end
        lower_skill = string.match(skill_html, "<th>下位スキル.-<td><a.->(.-)</a>") or json.null;
    end

    --[[skill_dict]]
    ::continue_skill_dict::
    skill_dict = skill_dict or {};
    skill_dict["skill_pt"] = skill_dict["skill_pt"] or {};
    skill_dict["skill_description"] = skill_dict["skill_description"] or {};
    skill_dict["upper_skill"] = skill_dict["upper_skill"] or {};
    skill_dict["lower_skill"] = skill_dict["lower_skill"] or {};
    skill_dict["skill_icon_name"] = skill_dict["skill_icon_name"] or {};

    skill_dict = {
        ["skill_pt"] = skill_pt,
        ["skill_description"] = skill_description,
        ["upper_skill"] = upper_skill,
        ["lower_skill"] = lower_skill,
        ["skill_icon_name"] = skill_icon_name
    }

    return skill_color, skill_rare, skill_name, skill_dict;
end

-- 傳入 html 和 element 的 id，將返回已處理好的 event_html
function parser.getEventHtmlById(html, id)
    assert(html and id,
        "\n[html_parser] html 或 id 是 nil。\n" .. "html: " .. tostring(html) .. " id: " .. tostring(id));

    local rare = nil;
    local owner_type = "character";

    local function tryGetRare(pattern, rarity)

        rare = string.match(html, pattern);

        if rare then return rarity; end

        return rare;
    end

    local owner_pattern = "<h1 class=\"_title\">【ウマ娘】(.-)%(";
    local event_owner = string.match(html, owner_pattern);

    local another_name = nil;

    local another_name_character_pattern = "<th.-名称.-<td.->(.-)</td.->"
    another_name = string.match(html, another_name_character_pattern);

    if another_name ~= nil then -- 此時還是 nil 就是支援卡
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(星1%).-</h1>", "1_star"); end
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(星2%).-</h1>", "2_star"); end
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(星3%).-</h1>", "3_star"); end
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(.-%).-</h1>", "3_star"); end
        -- if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(.-衣装.-%).-</h1>", "3_star"); end
        -- if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(ハロウィン%).-</h1>", "3_star"); end
        -- if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(クリスマス%).-</h1>", "3_star"); end
    else
        local another_name_card_pattern = "<th.-二つ名.-<td.->(.-)</td.->"
        another_name = string.match(html, another_name_card_pattern);

        owner_type = "support_card";
        rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(R.-%).-</h1>", "R")
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(SR.-%).-</h1>", "SR"); end
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(SSR.-%).-</h1>", "SSR"); end
        if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(.-%).-</h1>", "SSR"); end
        -- if rare == nil then rare = tryGetRare("<h1 class=\"_title\">【ウマ娘】.-%(.-配布.-%).-</h1>", "SSR"); end
    end
    --[[
    到這裡 another_name 還是 nil 就表示了連接請求被阻擋了
    所以 ms 要再調高
    ]]
    if not another_name then return nil end
    local event_owner_tag = "<event_owner>" .. event_owner .. "（" .. another_name .. "）" .. "</event_owner";

    local pattern = "<([%w]+)[%s+]id=\"(" .. id .. ")\"(.-)</body>";
    local tag, id, event_html = string.match(html, pattern);

    if event_html == nil then return end
    -- local pattern = "<[%w+][%s+]id=\"" .. id .. "\"(.-)</body>";
    -- local event_html = string.match(html, pattern);

    -- console:print(html);
    -- console:print(event_html);

    local final_html = event_owner_tag .. event_html;

    -- console:print("id=", id, "owner_type=", owner_type, "rare=", rare);
    return final_html, owner_type, rare;
end

-- 傳入 event_html ，並解析 html 後返回解析後的 event_dict
function parser.getEventDict(event_html)
    local event_dict = { --[[
        [event_owner] = {
            [event_name] = {
                [1] = {
                    ["choice_name"] = choice_name,
                    ["choice_effect"] = choice_effect
                },
                [2] = {
                    ["choice_name"] = choice_name,
                    ["choice_effect"] = choice_effect
                },
            },
        },
    ]]
    }

    -- 獲取 event_owner
    local event_owner = string.match(event_html, "<event_owner>(.-)</event_owner>");

    local event_idx = 1;

    for event_content in string.gmatch(event_html, "(<h4.->.-</table>)") do

        -- console:print("============================");
        -- console:print("イベント：\n", event_content);
        local event_name = string.match(event_content, "<h4.->(.-)</h4>");
        -- console:print("イベントタイトル: ", event_title);

        local choice_idx = 1;

        for choice_html in string.gmatch(event_content, "<tr.->(.-)</tr>") do

            local choice_name = string.match(choice_html, "<th.->(.-)</th.->");
            -- console:print("選択肢タイトル: ", choice_title);
            local choice_effect = string.match(choice_html, "<td.->(.-)</td.->");

            if choice_name == nil or choice_effect == nil then
                console:print(pe.yellow ..
                                  "【警告】getEventDict(): choice_title 或 choice_effect 是 nil\nchoice_title: " ..
                                  tostring(choice_name) .. "\nchoice_effect: " .. tostring(choice_effect) .. pe.reset);
                goto continue
            end

            --[[
                有一些角色的 choice_title 會有其他內容
                例如「423577」就有 「L'Arcで発生時： 」
                所以要再去從 tag 中篩選出需要的文字
            ]]
            -- if string.match(choice_title, "<hr>") ~= nil then
            -- local replaced_br_title = string.gsub(choice_title, "<br>", "\n");
            -- local replaced_hr_title = string.gsub(replaced_br_title, "<hr>", "\n--------------\n");
            -- local removed_span_title = string.gsub(replaced_hr_title, "<span.->(.-)</span>", "%1");
            -- local replaced_br_title = string.gsub(choice_title, "<br>", "\n");
            -- local replaced_hr_title = string.gsub(replaced_br_title, "<hr>", "\n--------------\n");
            --     local span_title_content = string.gsub(choice_title, "<span.->(.-)</span>", "%1");
            --     local replaced_span_title = "<span class=\"special_choice_title\">" .. span_title_content .. "</span>";

            --     choice_title = replaced_span_title;
            -- end

            --[[
                對 choice_effect 加工
            ]]
            -- choice_effect = fixWrongSkillName(choice_effect)
            -- choice_effect = fixWrongStatusName(choice_effect);
            -- choice_effect = placeTagToStatus(choice_effect);
            -- choice_effect = placeTagToSkillHint(choice_effect);
            -- choice_effect = placeTagToCondition(choice_effect);

            -- local replace_br_effect = string.gsub(choice_effect, "<br>", "\n")
            -- local replace_hr_effect = string.gsub(replace_br_effect, "<hr>", "\n--------------\n")
            -- console:print("選択肢効果: \n" .. replace_hr_effect);

            event_dict[event_name] = event_dict[event_name] or {};
            event_dict[event_name][choice_idx] = {
                ["choice_name"] = choice_name,
                ["choice_effect"] = choice_effect
            }

            choice_idx = choice_idx + 1;

            ::continue::
        end

        event_idx = event_idx + 1;
    end

    return event_dict, event_owner;
end

return parser;
