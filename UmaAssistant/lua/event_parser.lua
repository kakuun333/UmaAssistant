local pe = require("print_enhance");
local utility = require("utility");

parser = {}




-- 傳入 html 和 element 的 id，將返回已處理好的 event_html
function parser.getEventHtmlById(html, id)
    assert(html and id, "\n[html_parser] html 或 id 是 nil。\n" ..  "html: " .. tostring(html) .. " id: "..tostring(id));

    local owner_pattern = "<h1 class=\"_title\">【ウマ娘】(.-)%(";
    local event_owner = string.match(html, owner_pattern);

    local another_name = nil;

    local another_name_character_pattern = "<th.-名称.-<td.->(.-)</td.->"
    another_name = string.match(html, another_name_character_pattern);

    if another_name == nil then -- 此時還是 nil 就是支援卡
        local another_name_card_pattern = "<th.-二つ名.-<td.->(.-)</td.->"
        another_name = string.match(html, another_name_card_pattern);
    end

    --[[
    another_name 就表示了連接請求被阻擋了
    所以 ms 要再調高
    ]]

    local event_owner_tag = "<event_owner>"..event_owner.."（"..another_name.."）".."</event_owner";

    local pattern = "<([%w]+)[%s+]id=\"(" .. id .. ")\"(.-)</body>";
    local tag, id, event_html = string.match(html, pattern);

    if event_html == nil then return end;
    -- local pattern = "<[%w+][%s+]id=\"" .. id .. "\"(.-)</body>";
    -- local event_html = string.match(html, pattern);

    -- print(html);
    -- print(event_html);

    local final_html = event_owner_tag .. event_html;

    return final_html;
end




-- 傳入 event_html ，並解析 html 後返回解析後的 event_dict
function parser.getEventDict(event_html)
    local event_dict = {--[[
        ["event_owner"] = event_owner,
        ["event_list"] = {
            [event_1] = {
                ["event_title"] = event_title,
                ["choice_list"] = {
                    [choice_1] = {
                        ["choice_title"] = choice_title
                        ["choice_effect"] = choice_effect
                    },
                    [choice_2] = {
                        ["choice_title"] = choice_title
                        ["choice_effect"] = choice_effect
                    },
                },
            } 
        },
    ]]}


    -- 獲取 event_owner
    local event_owner = string.match(event_html, "<event_owner>(.-)</event_owner>");
    event_dict["event_owner"] = event_owner;
    event_dict["event_list"] = {};

    local event_idx = 1;

    for event_content in string.gmatch(event_html, "(<h4.->.-</table>)") do

        -- print("============================");
        -- print("イベント：\n", event_content);
        local event_title = string.match(event_content, "<h4.->(.-)</h4>");
        -- print("イベントタイトル: ", event_title);

        
        local choice_idx = 1;

        event_dict["event_list"]["event_"..tostring(event_idx)] = {
            ["event_title"] = event_title;
            ["choice_list"] = {};
        };


        for choice_html in string.gmatch(event_content, "<tr.->(.-)</tr>") do
            
            local choice_title = string.match(choice_html, "<th.->(.-)</th.->");
            -- print("選択肢タイトル: ", choice_title);
            local choice_effect = string.match(choice_html, "<td.->(.-)</td.->");
            
            if choice_title == nil or choice_effect == nil then
                print(pe.yellow.."【警告】getEventDict(): choice_title 或 choice_effect 是 nil\nchoice_title: "..tostring(choice_title).."\nchoice_effect: "..tostring(choice_effect)..pe.reset);
                goto continue;
            end

            --[[
                有一些角色的 choice_title 會有其他內容
                例如「423577」就有 「L'Arcで発生時： 」
                所以要再去從 tag 中篩選出需要的文字
            ]]
            if string.match(choice_title, "<hr>") ~= nil then 
                local replaced_br_title = string.gsub(choice_title, "<br>", "\n");
                local replaced_hr_title = string.gsub(replaced_br_title, "<hr>", "\n--------------\n");
                local removed_span_title = string.gsub(replaced_hr_title, "<span.->(.-)</span>", "%1");
                choice_title = removed_span_title;
            end


            local replace_br_effect = string.gsub(choice_effect, "<br>", "\n")
            local replace_hr_effect = string.gsub(replace_br_effect, "<hr>", "\n--------------\n")
            -- print("選択肢効果: \n" .. replace_hr_effect);
            
            event_dict["event_list"]["event_"..tostring(event_idx)]["choice_list"]["choice_"..tostring(choice_idx)] = {
                ["choice_title"] = choice_title,
                ["choice_effect"] = replace_hr_effect,
            }

            choice_idx = choice_idx + 1;
            
            ::continue::
        end

        event_idx = event_idx + 1;
    end

    return event_dict;
end

return parser;