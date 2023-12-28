import json
import re
import utility
import copy

# jp_data
event_data_jp = utility.read_json_file(r"../UmaData/event_data_jp.json");
skill_data_jp = utility.read_json_file(r"../UmaData/skill_data_jp.json");
scenario_event_data_jp = utility.read_json_file(r"../UmaData/scenario_event_data_jp.json");

# select_character_data
select_character_data = utility.read_json_file(r"../UmaData/select_character_data.json");

# translation_data
translation_data = utility.read_json_file(r"../UmaData/translation_data.json");

# missed_data
missed_data = utility.read_json_file(r"../UmaData/missed_data.json");

# convert_data
char_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_cvt_tw_char.json");
card_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_cvt_tw_card.json");
skill_convert_data = utility.read_json_file(r"../UmaData/skill_data_jp_cvt_tw.json");
scenario_convert_data = utility.read_json_file(r"../UmaData/scenario_event_data_jp_cvt_tw.json");



event_data_tw = {
    "character": {
        "1_star": {},
        "2_star": {},
        "3_star": {},
    },
    "support_card": {
        "R": {},
        "SR": {},
        "SSR": {},
    },
};

event_data_jp_trans_tw = copy.deepcopy(event_data_tw);

skill_data_tw = {
    "blue": {
        "normal": {

        },
        "rare": {

        }
    },
    "green": {
        "normal": {

        },
        "rare": {
            
        }
    },
    "red": {
        "normal": {

        },
        "rare": {
            
        }
    },
    "yellow": {
        "normal": {

        },
        "rare": {
            
        }
    }
}

skill_data_jp_trans_tw = copy.deepcopy(skill_data_tw);


scenario_event_data_tw = {
    "URA": {
        
    },
    "aoharu": {
        
    },
    "meikura": {
        
    },
    "gurarai": {
        
    },
    "guramasu": {
        
    },
    "L'Arc": {

    },
};


def convert_choice_effect_jp_to_tw(choice_effect, jp_event_owner = None, tw_event_owner = None, cvt_skill_data = True):
    # 修正日文技能名稱
    for incorrect_skill_title, correct_skill_title in missed_data["jp_to_tw"]["skill_title"].items():
        choice_effect = re.sub(rf'{incorrect_skill_title}(?!◯)', correct_skill_title, choice_effect, flags=re.IGNORECASE);

    # 翻譯 jp 轉 tw
    for jp, tw in translation_data["jp_to_tw"]["choice_effect"].items():
        if (jp == "スタミナ"):
            choice_effect = re.sub(rf'{jp}(?!キープ)', tw, choice_effect, flags=re.IGNORECASE);
        elif (jp == "スピード"):
            choice_effect = re.sub(rf'{jp}(?!スター|イーター)', tw, choice_effect, flags=re.IGNORECASE);
        elif (jp == "アップ"): # 避免替換到技能 ペースアップ、テンポアップ
            choice_effect = re.sub(rf'{jp}(?!』)', tw, choice_effect, flags=re.IGNORECASE);
        elif (jp == "or"):
            choice_effect = re.sub(rf'(?![a-zA-Z]){jp}(?![a-zA-Z])', tw, choice_effect, flags=re.IGNORECASE);
        else:
            choice_effect = re.sub(jp, tw, choice_effect, flags=re.IGNORECASE);


    if (cvt_skill_data):
        # 技能名稱 jp 轉 tw
        try:
            # re.search() 找到一個之後就停了，所以一個 choice_effect 中有兩個 skill_hint 的話就會缺漏匹配，
            # 所以改成 re.findall() 找到 choice_effect 裡面所有的 skill_hint 之後再替換成 tw_skill_title;
            jp_skill_title_match = re.findall(r'<span class="skill_hint">『(.+?)』</span>(的靈感Lv)?', choice_effect)
            if jp_skill_title_match:
                for match in jp_skill_title_match:
                    jp_skill_title = match[0];

                    # print(jp_skill_title); #######################################################################
                    try:
                        tw_skill_title = skill_convert_data[jp_skill_title]["tw_skill_title"];
                        
                        choice_effect = re.sub(jp_skill_title, tw_skill_title, choice_effect);
                    except:
                        pass;
        except:
            print(choice_effect);
            pass;
        # 技能名稱 jp 轉 tw

    # 情誼量條的名稱 jp 轉 tw
    try:
        owner_name_pattern = r"(.+)（.+）";
        jp_event_owner = re.match(owner_name_pattern, jp_event_owner).group(1);
        tw_event_owner = re.match(owner_name_pattern, tw_event_owner).group(1);
        choice_effect = re.sub(jp_event_owner, tw_event_owner, choice_effect, flags=re.IGNORECASE);
    except:
        pass;
    # 情誼量條的名稱 jp 轉 tw



    return choice_effect;

def convert_choice_title_jp_to_tw(choice_title):
    for jp, tw in translation_data["jp_to_tw"]["choice_title"].items():
        # 用 re.escape() 來避開正規表達式的特殊字符
        # 例如：『ただいま』か……(サイレンススズカ) 的 ()
        choice_title = re.sub(re.escape(jp), tw, choice_title)

    return choice_title;



##### select_character_data.json #####
def select_character_jp_owner_to_tw_owner():
    for jp_event_owner, jp_event_owner_v in char_convert_data.items():
        
        for origin_name, cvt_name in missed_data["jp_to_tw"]["event_owner"].items():
            if (jp_event_owner == cvt_name):
                jp_event_owner = origin_name;

        for idx, char_data in enumerate(select_character_data):

            if (char_data["jp_event_owner"] == jp_event_owner):
                select_character_data[idx]["tw_event_owner"] = jp_event_owner_v["tw_event_owner"];
                # tmp_dict = {};
                # tmp_dict["icon"] = char_data["icon"];
                # tmp_dict["jp_event_owner"] = char_data["jp_event_owner"];
                # tmp_dict["tw_event_owner"] = char_name_v["tw_event_owner"];

                # new_select_character_data.append(tmp_dict);


select_character_jp_owner_to_tw_owner();

json_string = json.dumps(select_character_data, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/select_character_data.json", json_string);


##### skill_data_tw.json #####
def convert_to_skill_data_tw(convert_data):
    for color, color_v in skill_data_jp.items():
        for rare, rare_v in color_v.items():
            for jp_skill_title, jp_skill_title_v in rare_v.items():
                if jp_skill_title in convert_data:
                    skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]] = {};
                    for key, value in jp_skill_title_v.items():

                        if (key == "upper_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_upper_skill"];
                        elif (key == "lower_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_lower_skill"];
                        elif (key == "skill_effect"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_skill_effect"];
                        else:
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = value;

convert_to_skill_data_tw(skill_convert_data);

json_string = json.dumps(skill_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/skill_data_tw.json", json_string);

##### event_data_tw.json #####
def convert_to_event_data_tw(convert_data):
    for owner_type, owner_type_v in event_data_jp.items():
        for rare, rare_v in owner_type_v.items():
            for jp_event_owner, jp_event_owner_v in rare_v.items():
                if (jp_event_owner in missed_data["jp_to_tw"]["event_owner"]):
                    jp_event_owner = missed_data["jp_to_tw"]["event_owner"][jp_event_owner];
                if jp_event_owner in convert_data:
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]] = {};
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"] = [];

                    # print(card_convert_data[jp_event_owner]["tw_event_owner"]);
                    for event in jp_event_owner_v["event"]:
                        tw_event_obj = {};
                        for jp_event_title, jp_event_title_v in event.items():
                            if (jp_event_title in missed_data["jp_to_tw"]["event_title"]):
                                jp_event_title = missed_data["jp_to_tw"]["event_title"][jp_event_title];
                            if jp_event_title in convert_data[jp_event_owner]["event_title_dict"]:
                                tw_event_obj[convert_data[jp_event_owner]["event_title_dict"][jp_event_title]] = [];
                                # event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"].append()
                                for choice_info in jp_event_title_v:
                                    tw_choice_obj = {};

                                    tw_event_owner = convert_data[jp_event_owner]["tw_event_owner"];

                                    for key, value in choice_info.items():
                                        if (key == "choice_effect"):
                                            value = convert_choice_effect_jp_to_tw(value, jp_event_owner, tw_event_owner);
                                        else:
                                            value = convert_choice_title_jp_to_tw(value);
                                        
                                        tw_choice_obj[key] = value;

                                    tw_event_obj[convert_data[jp_event_owner]["event_title_dict"][jp_event_title]].append(tw_choice_obj);
                            else:
                                continue;
                        if (tw_event_obj):
                            event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"].append(tw_event_obj);

convert_to_event_data_tw(char_convert_data);
convert_to_event_data_tw(card_convert_data);

json_string = json.dumps(event_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/event_data_tw.json", json_string);

##### event_data_jp_trans_tw.json #####
def convert_to_event_data_jp_trans_tw():
    for owner_type, owner_type_v in event_data_jp.items():
        for rare, rare_v in owner_type_v.items():
            for jp_event_owner, jp_event_owner_v in rare_v.items():
                event_data_jp_trans_tw[owner_type][rare][jp_event_owner] = {};
                event_data_jp_trans_tw[owner_type][rare][jp_event_owner]["event"] = [];
                for event in jp_event_owner_v["event"]:
                    event_obj = {};
                    for jp_event_title, jp_event_title_v in event.items():
                        event_obj[jp_event_title] = [];
                        for choice_info in jp_event_title_v:
                            choice_obj = {};

                            for key, value in choice_info.items():
                                if (key == "choice_effect"):
                                    value = convert_choice_effect_jp_to_tw(value, jp_event_owner, cvt_skill_data=False);
                                else:
                                    value = convert_choice_title_jp_to_tw(value);

                                choice_obj[key] = value;

                            event_obj[jp_event_title].append(choice_obj);
                    
                    event_data_jp_trans_tw[owner_type][rare][jp_event_owner]["event"].append(event_obj);

convert_to_event_data_jp_trans_tw()
json_string = json.dumps(event_data_jp_trans_tw, indent=1, ensure_ascii=False);

utility.write_file("../UmaData/event_data_jp_trans_tw.json", json_string);

##### skill_data_jp_trans_tw.json #####
def convert_to_skill_data_jp_trans_tw(convert_data):
    for color, color_v in skill_data_jp.items():
        for rare, rare_v in color_v.items():
            for jp_skill_title, jp_skill_title_v in rare_v.items():
                skill_data_jp_trans_tw[color][rare][jp_skill_title] = {};
                for key, value in jp_skill_title_v.items():
                    if (key == "skill_effect"):
                        try:
                            skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = convert_data[jp_skill_title]["tw_skill_effect"];
                        except: # 沒有中文翻譯的情況
                            skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = value;
                    
                    else:
                        skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = value;

convert_to_skill_data_jp_trans_tw(skill_convert_data);

json_string = json.dumps(skill_data_jp_trans_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/skill_data_jp_trans_tw.json", json_string);


##### scenario_event_data_tw.json #####
def convert_to_scenario_event_data_tw(convert_data):
    for scenario_type, scenario_type_v in scenario_event_data_jp.items():
        for jp_event_title, jp_event_title_v in scenario_type_v.items():
            if (jp_event_title in missed_data["jp_to_tw"]["event_title"]):
                jp_event_title = missed_data["jp_to_tw"]["event_title"][jp_event_title];
            if jp_event_title in convert_data:
                scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]] = [];
                for choice in jp_event_title_v:
                    tw_choice_obj = {};

                    for key, value in choice.items():
                        if (key == "choice_effect"):
                            value = convert_choice_effect_jp_to_tw(value);
                        elif (key == "choice_title"):
                            value = convert_choice_title_jp_to_tw(value);

                        tw_choice_obj[key] = value;
                    scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]].append(tw_choice_obj);



convert_to_scenario_event_data_tw(scenario_convert_data);

json_string = json.dumps(scenario_event_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/scenario_event_data_tw.json", json_string);