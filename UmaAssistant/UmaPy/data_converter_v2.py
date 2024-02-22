import re
import json
import copy
import sys

import util
from umaenum import *
from umaglobal import *

###############################################################################################

event_data_jp = util.read_json("../UmaData/event_data_jp.json");
skill_data_jp = util.read_json("../UmaData/skill_data_jp.json");
enhance_skill_data_jp = util.read_json("../UmaData/enhance_skill_data_jp.json");

# select_character_data
select_character_data = util.read_json("../UmaData/select_character_data.json");

############### convert_data ###############
# translation_data
translation_data = util.read_json("../UmaData/convert_data/translation_data.json");

# missed_data
missed_data = util.read_json("../UmaData/convert_data/missed_data.json");

char_cvt_data = util.read_json("../UmaData/convert_data/event_data_jp_cvt_tw_char.json");
sapoka_cvt_data = util.read_json("../UmaData/convert_data/event_data_jp_cvt_tw_card.json");
scenario_cvt_data = util.read_json("../UmaData/convert_data/event_data_jp_cvt_tw_scenario.json");
skill_cvt_data = util.read_json("../UmaData/convert_data/skill_data_jp_cvt_tw.json");

# process_choice_effect_data
process_choice_effect_data = util.read_json("../UmaData/convert_data/process_choice_effect_data.json");

# fix_choice_effect_data
fix_choice_effect_data = util.read_json("../UmaData/convert_data/fix_choice_effect_data.json");

###############################################################################################

# event_data 
event_data_tw = copy.deepcopy(DEFAULT_EVENT_DATA_DICT);
event_data_jp_trans_tw = copy.deepcopy(DEFAULT_EVENT_DATA_DICT);

# skill_data
skill_data_tw = copy.deepcopy(DEFAULT_SKILL_DATA_DICT);
skill_data_jp_trans_tw = copy.deepcopy(DEFAULT_SKILL_DATA_DICT);

# enhance_skill_data
enhance_skill_data_tw = {};


###############################################################################################
# 刪除 event_data_jp.json 值是空陣列的 event_name
# 有一些事件沒有選項也沒有效果，所以 dump_event_data.py 會把它變成空陣列
def del_empty_value_event_name_key():
    del_event_name_obj_list = [];

    # 找出需要刪除的 event_name 和 路徑
    for rare, rare_v in event_data_jp["character"].items():
        for event_owner, event_owner_v in rare_v.items():
            for event_name, event_name_v in event_owner_v.items():
                if event_name_v == []:
                    del_event_name_obj = {
                        "rare": rare,
                        "event_owner": event_owner,
                        "event_name": event_name,
                    }
                    del_event_name_obj_list.append(del_event_name_obj);

    # 刪除值是空陣列的 event_name 鍵
    for del_event_obj in del_event_name_obj_list:
        del event_data_jp["character"][del_event_obj["rare"]][del_event_obj["event_owner"]][del_event_obj["event_name"]];

    util.write_json("../UmaData/event_data_jp.json", event_data_jp);

del_empty_value_event_name_key();
###############################################################################################
# 修正 event_data_jp.json 的 choice_effect

def fix_choice_effect():
    
    for rare, rare_v in event_data_jp["character"].items():
        for event_owner, event_owner_v in rare_v.items():
            for event_name, event_name_v in event_owner_v.items():
                if event_name == "新年の抱負": # 修正所有角色的「新年の抱負」事件的第一個選項的效果
                    # +25 改成 +10
                    event_data_jp["character"][rare][event_owner][event_name][0]["choice_effect"] = util.sub(event_data_jp["character"][rare][event_owner][event_name][0]["choice_effect"], "25", "10");
                elif event_name == "初詣": # 修正所有角色的「初詣」事件的第二個選項的效果
                    # +8 改成 +5
                    event_data_jp["character"][rare][event_owner][event_name][1]["choice_effect"] = util.sub(event_data_jp["character"][rare][event_owner][event_name][1]["choice_effect"], "8", "5");

    # 修正單一事件效果
    for rare, rare_v in event_data_jp["character"].items():
        for event_owner, event_owner_v in rare_v.items():
            if event_owner in fix_choice_effect_data["character"]:
                for fix_event_name, fix_event_name_v in fix_choice_effect_data["character"][event_owner].items():

                    for choice_idx, choice_value in enumerate(fix_event_name_v):
                        fix_event_name_v[choice_idx]["choice_effect"] = util.process_choice_effect(choice_value["choice_effect"], process_choice_effect_data, skill_data_jp)

                    event_data_jp["character"][rare][event_owner][fix_event_name] = fix_event_name_v;

    util.write_json("../UmaData/event_data_jp.json", event_data_jp);


fix_choice_effect();
###############################################################################################
# 修正某些 event_name 含有 larc_event_name 而導致無法匹配事件名稱和無法轉換繁中服事件名稱的問題
# 作法：
# 1. 把原本該有的事件名稱去除掉 larc_event_name 後獨立成一個事件資料
# 2. 把 larc_event_name 提取出來後獨立成一個事件資料
# 3. 刪除含有 larc_event_name 的 event_name 鍵
def fix_larc_event_name():
    create_event_list = [];
    del_event_list = [];

    for event_type, event_type_v in event_data_jp.items():
        if (event_type == "scenario"): continue;
        for rare, rare_v in event_type_v.items():
            for event_owner, event_owner_v in rare_v.items():
                for original_event_name, original_event_name_v in event_owner_v.items():
                    larc_event_name = re.search(r"パリの街にて|彼の都の思い出は|その日を信じて|温かなメッセージ", original_event_name);
                    if larc_event_name:
                        subed_original_event_name = re.sub(rf"(（)?{larc_event_name.group()}(）)?", "", original_event_name);
                        # print("subed_original_event_name: ", subed_original_event_name);

                        larc_event_name = larc_event_name.group();
                        # print("larc_event_name: ", larc_event_name)
                        

                        subed_original_event_name_obj = {
                            "event_type": event_type,
                            "rare": rare,
                            "event_owner": event_owner,
                            "event_name": subed_original_event_name,
                            "choice_list": [],
                        }

                        larc_event_name_obj = {
                            "event_type": event_type,
                            "rare": rare,
                            "event_owner": event_owner,
                            "event_name": larc_event_name,
                            "choice_list": [],
                        }

                        del_event_name_obj = {
                            "event_type": event_type,
                            "rare": rare,
                            "event_owner": event_owner,
                            "event_name": original_event_name,
                        }
                        del_event_list.append(del_event_name_obj);

                        for choice_dict in original_event_name_v:
                            larc_choice_name_search = re.search(r"(<hr>)?(<br>)?L'Arcで発生時：<br>(.+)", choice_dict["choice_name"]);
                            # 如果找到 larc_choice_name
                            # choice_obj
                            choice_obj = {
                                "choice_name": "",
                                "choice_effect": ""
                            };
                            larc_choice_obj = copy.deepcopy(choice_obj);

                            # 獲取去除 larc_choice_name 的 choice_name
                            subed_original_choice_name = re.sub(r"(<hr>)?(<br>)?L'Arcで発生時：<br>(.+)", "", choice_dict["choice_name"]);
                            choice_obj["choice_name"] = subed_original_choice_name;
                            choice_obj["choice_effect"] = choice_dict["choice_effect"];
                            subed_original_event_name_obj["choice_list"].append(choice_obj);
                            
                            # 有 larc_choice_name 的情況
                            if larc_choice_name_search:
                                larc_choice_name = larc_choice_name_search.group(3);
                            else: # choice_name 是「選択肢なし」的情況
                                larc_choice_name = choice_obj["choice_name"];

                            larc_choice_obj["choice_name"] = larc_choice_name;
                            larc_choice_obj["choice_effect"] = choice_dict["choice_effect"];
                            larc_event_name_obj["choice_list"].append(larc_choice_obj);
                        
                        create_event_list.append(subed_original_event_name_obj);
                        create_event_list.append(larc_event_name_obj);


    # 刪除有包含 larc_event_name 的 event_name 鍵
    for del_event_obj in del_event_list:
        del event_data_jp[del_event_obj["event_type"]][del_event_obj["rare"]][del_event_obj["event_owner"]][del_event_obj["event_name"]];

    # 創建分離 larc_event_name 的 event 和 larc_event 的 event_name 鍵
    for create_event_obj in create_event_list:
        event_data_jp[create_event_obj["event_type"]][create_event_obj["rare"]][create_event_obj["event_owner"]][create_event_obj["event_name"]] = create_event_obj["choice_list"];

    util.write_json("../UmaData/event_data_jp.json", event_data_jp);



print("開始 fix_larc_event_name");
fix_larc_event_name();
print("結束 fix_larc_event_name");


###############################################################################################
# skill_effect_type 是 "skill_effect_title" or "skill_effect_data"
def trans_enhance_skill_data_jp_to_tw(skill_effect_title, skill_effect_data):

    if (skill_effect_title == "スタート時間"):
        skill_effect_title = translation_data["jp_to_tw"]["skill_effect_title"][skill_effect_title];
        skill_effect_data = re.sub(r"(\d+\.\d+ 倍)に補正", r"調整為 \1", skill_effect_data);
    elif (skill_effect_title == "人気"):
        skill_effect_title = translation_data["jp_to_tw"]["skill_effect_title"][skill_effect_title];
        skill_effect_data = re.sub(r"(\d+)番人気", r"第\1人氣", skill_effect_data);

    for jp, tw in translation_data["jp_to_tw"]["skill_effect_title"].items():
        skill_effect_title = re.sub(jp, tw, skill_effect_title);

    for jp, tw in translation_data["jp_to_tw"]["skill_effect_data"].items():
        try:
            skill_effect_data = re.sub(jp, tw, skill_effect_data); # TypeError: expected string or bytes-like object, got 'NoneType'
        except:
            pass;

    return skill_effect_title, skill_effect_data;

def cvt_enhance_skill_data_jp_to_tw():
    # enhance_skill_data_jp
    # skill_convert_data
    for skill_name, skill_name_v in enhance_skill_data_jp.items():
        if skill_name in skill_cvt_data:
            enhance_skill_data_tw[skill_cvt_data[skill_name]["tw_skill_name"]] = {
                "skill_effect": {},
                "skill_condition": {},
            };

            for skill_data_type, skill_data_type_v in skill_name_v.items():
                for skill_effect_title, skill_effect_data in skill_data_type_v.items():
                    skill_effect_title, skill_effect_data = trans_enhance_skill_data_jp_to_tw(skill_effect_title, skill_effect_data);

                    enhance_skill_data_tw[skill_cvt_data[skill_name]["tw_skill_name"]][skill_data_type][skill_effect_title] = skill_effect_data;


cvt_enhance_skill_data_jp_to_tw();
util.write_json("../UmaData/enhance_skill_data_tw.json", enhance_skill_data_tw);
###############################################################################################
##### event_data_tw.json #####

def convert_choice_name_jp_to_tw(choice_name):
    if choice_name in translation_data["jp_to_tw"]["choice_name"]:
        tw = translation_data["jp_to_tw"]["choice_name"][choice_name];

        # 用 re.escape() 來避開正規表達式的特殊字符
        # 例如：『ただいま』か……(サイレンススズカ) 的 ()
        choice_name = re.sub(re.escape(choice_name), tw, choice_name);

    # for jp, tw in translation_data["jp_to_tw"]["choice_name"].items():
    #     if re.search(jp, choice_name):
    #         choice_name = re.sub(jp, tw, choice_name);


    # for jp, tw in translation_data["jp_to_tw"]["choice_title"].items():
    #     # 用 re.escape() 來避開正規表達式的特殊字符
    #     # 例如：『ただいま』か……(サイレンススズカ) 的 ()
    #     choice_title = re.sub(re.escape(jp), tw, choice_title)

    return choice_name;

def convert_choice_effect_jp_to_tw(choice_effect, jp_event_owner = None, tw_event_owner = None, cvt_skill_data = True):
    # 修正日文技能名稱
    for incorrect_skill_title, correct_skill_title in missed_data["jp_to_tw"]["skill_title"].items():
        choice_effect = re.sub(rf'{incorrect_skill_title}(?!◯)', correct_skill_title, choice_effect, flags=re.IGNORECASE);

    # 翻譯 jp 轉 tw
    for jp, tw in translation_data["jp_to_tw"]["choice_effect"].items():
        if (jp == "スタミナ"):
            choice_effect = re.sub(rf'{jp}(?!キープ)', tw, choice_effect, flags=re.IGNORECASE);
        elif (jp == "スピード"): # 避免替換到技能 スピードスター、スピードイーター
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
            # 所以改成 re.findall() 找到 choice_effect 裡面所有的 skill_hint 之後再替換成 tw_skill_name;
            jp_skill_title_match = re.findall(r'<span class="skill_hint">『(.+?)』</span>(的靈感Lv)?', choice_effect)
            if jp_skill_title_match:
                for match in jp_skill_title_match:
                    jp_skill_title = match[0];

                    # print(jp_skill_title); #######################################################################
                    try:
                        tw_skill_name = skill_cvt_data[jp_skill_title]["tw_skill_name"];
                        
                        choice_effect = re.sub(jp_skill_title, tw_skill_name, choice_effect);
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

def convert_to_event_data_tw(eventDataType, convert_data):

    if (eventDataType == EventDataType.SCENARIO):
        for scenario_type, scenario_type_v in event_data_jp[eventDataType].items():
            for jp_event_name, jp_event_name_v in scenario_type_v.items():
                if (jp_event_name in missed_data["jp_to_tw"]["event_name"]):
                    jp_event_name = missed_data["jp_to_tw"]["event_name"][jp_event_name];
                if jp_event_name in convert_data:
                    event_data_tw[eventDataType][scenario_type][convert_data[jp_event_name]["tw_event_name"]] = [];
                    for choice in jp_event_name_v:
                        tw_choice_obj = {};

                        for key, value in choice.items():
                            if (key == "choice_effect"):
                                value = convert_choice_effect_jp_to_tw(value);
                            elif (key == "choice_name"):
                                value = convert_choice_name_jp_to_tw(value);

                            tw_choice_obj[key] = value;
                        event_data_tw[eventDataType][scenario_type][convert_data[jp_event_name]["tw_event_name"]].append(tw_choice_obj);
    else:
        for event_type, event_type_v in event_data_jp.items():
            
            if event_type == EventDataType.SCENARIO: continue;

            for rare, rare_v in event_type_v.items():
                for jp_event_owner, jp_event_owner_v in rare_v.items():

                    if (jp_event_owner in missed_data["jp_to_tw"]["event_owner"]):
                        jp_event_owner = missed_data["jp_to_tw"]["event_owner"][jp_event_owner];
                    
                    if jp_event_owner in convert_data:

                        event_data_tw[event_type][rare][convert_data[jp_event_owner]["tw_event_owner"]] = {};

                        for jp_event_name, jp_event_name_v in jp_event_owner_v.items():

                            if (jp_event_name in missed_data["jp_to_tw"]["event_name"]):
                                jp_event_name = missed_data["jp_to_tw"]["event_name"][jp_event_name];
                            
                            if jp_event_name in convert_data[jp_event_owner]["event_name_dict"]:

                                event_data_tw[event_type][rare][convert_data[jp_event_owner]["tw_event_owner"]][convert_data[jp_event_owner]["event_name_dict"][jp_event_name]] = []

                                for choice_info in jp_event_name_v:
                                    tw_choice_obj = {};

                                    tw_event_owner = convert_data[jp_event_owner]["tw_event_owner"];

                                    for key, value in choice_info.items():
                                        if (key == "choice_effect"):
                                            value = convert_choice_effect_jp_to_tw(value, jp_event_owner, tw_event_owner);
                                        else:
                                            value = convert_choice_name_jp_to_tw(value);
                                        
                                        tw_choice_obj[key] = value;
                            
                                    event_data_tw[event_type][rare][convert_data[jp_event_owner]["tw_event_owner"]][convert_data[jp_event_owner]["event_name_dict"][jp_event_name]].append(tw_choice_obj);
                            else:
                                continue;

convert_to_event_data_tw(EventDataType.SAPOKA, sapoka_cvt_data)
convert_to_event_data_tw(EventDataType.CHARACTER, char_cvt_data)
convert_to_event_data_tw(EventDataType.SCENARIO, scenario_cvt_data)
util.write_json("../UmaData/event_data_tw.json", event_data_tw);


###############################################################################################
##### event_data_jp_trans_tw.json #####
def convert_to_event_data_jp_trans_tw(eventDataType):
    if (eventDataType == EventDataType.SCENARIO):
        print("scenario");
    else:
        for event_type, event_type_v in event_data_jp.items():
            
            if event_type == EventDataType.SCENARIO: continue;

            for rare, rare_v in event_type_v.items():
                for event_owner, event_owner_v in rare_v.items():
                    # 創建 [event_owner] = {}
                    event_data_jp_trans_tw[event_type][rare][event_owner] = {};

                    for event_name, event_name_v in event_owner_v.items():
                        # 創建 [event_name] = []
                        event_data_jp_trans_tw[event_type][rare][event_owner][event_name] = [];

                        for choice_info in event_name_v:
                            choice_obj = {};

                            for key, value in choice_info.items():
                                if (key == "choice_effect"):
                                    value = convert_choice_effect_jp_to_tw(value, event_owner, cvt_skill_data=False);
                                
                                choice_obj[key] = value;
                                
                            event_data_jp_trans_tw[event_type][rare][event_owner][event_name].append(choice_obj);

convert_to_event_data_jp_trans_tw(EventDataType.SAPOKA)
convert_to_event_data_jp_trans_tw(EventDataType.CHARACTER)
convert_to_event_data_jp_trans_tw(EventDataType.SCENARIO)
util.write_json("../UmaData/event_data_jp_trans_tw.json", event_data_jp_trans_tw);

###############################################################################################
##### skill_data_jp_trans_tw.json #####
def convert_to_skill_data_jp_trans_tw(convert_data):
    for color, color_v in skill_data_jp.items():
        for rare, rare_v in color_v.items():
            for jp_skill_title, jp_skill_title_v in rare_v.items():
                skill_data_jp_trans_tw[color][rare][jp_skill_title] = {};
                for key, value in jp_skill_title_v.items():
                    if (key == "skill_description"):
                        try:
                            skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = convert_data[jp_skill_title]["tw_skill_description"];
                        except: # 沒有中文翻譯的情況
                            skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = value;
                    
                    else:
                        skill_data_jp_trans_tw[color][rare][jp_skill_title][key] = value;

convert_to_skill_data_jp_trans_tw(skill_cvt_data);
util.write_json("../UmaData/skill_data_jp_trans_tw.json", skill_data_jp_trans_tw);

###############################################################################################
##### skill_data_tw.json #####
def convert_to_skill_data_tw(convert_data):
    for color, color_v in skill_data_jp.items():
        for rare, rare_v in color_v.items():
            for jp_skill_title, jp_skill_title_v in rare_v.items():
                if jp_skill_title in convert_data:
                    skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_name"]] = {};
                    for key, value in jp_skill_title_v.items():

                        if (key == "upper_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_name"]][key] = convert_data[jp_skill_title]["tw_upper_skill"];
                        elif (key == "lower_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_name"]][key] = convert_data[jp_skill_title]["tw_lower_skill"];
                        elif (key == "skill_description"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_name"]][key] = convert_data[jp_skill_title]["tw_skill_description"];
                        else:
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_name"]][key] = value;

convert_to_skill_data_tw(skill_cvt_data);
util.write_json("../UmaData/skill_data_tw.json", skill_data_tw);

###############################################################################################
##### select_character_data.json #####
def select_character_jp_owner_to_tw_owner():
    for jp_event_owner, jp_event_owner_v in char_cvt_data.items():
        
        # for origin_name, cvt_name in missed_data["jp_to_tw"]["event_owner"].items():
        #     if (jp_event_owner == cvt_name):
        #         jp_event_owner = origin_name;

        for idx, char_data in enumerate(select_character_data):

            if (char_data["jp_event_owner"] == jp_event_owner):
                select_character_data[idx]["tw_event_owner"] = jp_event_owner_v["tw_event_owner"];
                # tmp_dict = {};
                # tmp_dict["icon"] = char_data["icon"];
                # tmp_dict["jp_event_owner"] = char_data["jp_event_owner"];
                # tmp_dict["tw_event_owner"] = char_name_v["tw_event_owner"];

                # new_select_character_data.append(tmp_dict);


select_character_jp_owner_to_tw_owner();
util.write_json("../UmaData/select_character_data.json", select_character_data);

###############################################################################################
##### event_name_data_jp.json ##### event_name_data_tw.json #####

def get_same_event_name_dict(event_data_language):
    same_event_name_dict = {};
    event_data = {};

    if event_data_language == "tw":
        event_data = event_data_tw;
    elif event_data_language == "jp":
        event_data = event_data_jp

    for event_type, event_type_v in event_data.items():
        
        same_event_name_dict[event_type] = {};

        if event_type == EventDataType.SCENARIO:
            for scenario_type, scenario_type_v in event_type_v.items():
                for event_name, event_name_v in scenario_type_v.items():
                    same_event_name_dict[event_type][event_name] = event_name;
        else:
            for rare, rare_v in event_type_v.items():
                for event_owner, event_owner_v in rare_v.items():
                    for event_name, event_name_v in event_owner_v.items():
                        same_event_name_dict[event_type][event_name] = event_name;

    return same_event_name_dict;

def create_event_name_data():
    event_name_data_jp = copy.deepcopy(DEFAULT_EVENT_NAME_DATA_DICT);
    same_event_name_dict_jp = get_same_event_name_dict("jp");

    for event_type, event_type_v in same_event_name_dict_jp.items():
        for event_name, event_name_v in event_type_v.items():
            event_name_data_jp[event_type].append(event_name);
    
    util.write_json("../UmaData/event_name_data_jp.json", event_name_data_jp);

    # -----------------------------------------------------------------------------------

    event_name_data_tw = copy.deepcopy(DEFAULT_EVENT_NAME_DATA_DICT);
    same_event_name_dict_tw = get_same_event_name_dict("tw");

    for event_type, event_type_v in same_event_name_dict_tw.items():
        for event_name, event_name_v in event_type_v.items():
            event_name_data_tw[event_type].append(event_name);

    util.write_json("../UmaData/event_name_data_tw.json", event_name_data_tw);


create_event_name_data();


