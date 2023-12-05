import json
import re
import utility

# jp_data
event_data_jp = utility.read_json_file(r"../UmaData/event_data_jp.json");
skill_data_jp = utility.read_json_file(r"../UmaData/skill_data_jp.json");
scenario_event_data_jp = utility.read_json_file(r"../UmaData/scenario_event_data_jp.json");

# translation_data
translation_data = utility.read_json_file(r"../UmaData/translation_data.json");

# convert_data
char_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_char.json");
card_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_card.json");
skill_convert_data = utility.read_json_file(r"../UmaData/skill_data_jp_to_tw.json");
scenario_convert_data = utility.read_json_file(r"../UmaData/scenario_event_data_jp_to_tw.json");



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


def convert_choice_effect_jp_to_tw(choice_effect, jp_event_owner = None, tw_event_owner = None):
    # 翻譯 jp 轉 tw
    for jp, tw in translation_data["jp_to_tw"]["choice_effect"].items():
        if (jp == "スタミナ"):
            choice_effect = re.sub(rf'{jp}(?!キープ)', tw, choice_effect, flags=re.IGNORECASE);
        elif (jp == "スピード"):
            choice_effect = re.sub(rf'{jp}(?!スター)', tw, choice_effect, flags=re.IGNORECASE);
        else:
            choice_effect = re.sub(jp, tw, choice_effect, flags=re.IGNORECASE);

    # 技能名稱 jp 轉 tw
    try:
        jp_skill_title = re.search(r'<span class="skill_hint">『(.+?)』</span>[的靈感Lv]?', choice_effect)
        if jp_skill_title:
            jp_skill_title = jp_skill_title.group(1)
            print(jp_skill_title)
        
        # print(jp_skill_title)
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
        choice_title = re.sub(jp, tw, choice_title, flags=re.IGNORECASE)

    return choice_title;






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
                # if jp_event_owner in convert_data:
                if jp_event_owner in convert_data:
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]] = {};
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"] = [];

                    # print(card_convert_data[jp_event_owner]["tw_event_owner"]);
                    for event in jp_event_owner_v["event"]:
                        tw_event_obj = {};
                        for jp_event_title, jp_event_title_v in event.items():
                            if jp_event_title in convert_data[jp_event_owner]["event_title_dict"]:
                                tw_event_obj[convert_data[jp_event_owner]["event_title_dict"][jp_event_title]] = []
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

##### scenario_event_data_tw.json #####
def convert_to_scenario_event_data_tw(convert_data):
    for scenario_type, scenario_type_v in scenario_event_data_jp.items():
        for jp_event_title, jp_event_title_v in scenario_type_v.items():
            if jp_event_title in convert_data:
                scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]] = [];
                for choice in jp_event_title_v:
                    tw_choice_obj = {};

                    for key, value in choice.items():
                        if (key == "choice_effect"):
                            value = convert_choice_effect_jp_to_tw(value);
                        else:
                            value = convert_choice_title_jp_to_tw(value);

                        tw_choice_obj[key] = value;
                    scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]].append(tw_choice_obj);

convert_to_scenario_event_data_tw(scenario_convert_data);

json_string = json.dumps(scenario_event_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/scenario_event_data_tw.json", json_string);