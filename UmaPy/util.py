import os
import re
import json
from typing import Union

# 獲取腳本所在的路徑
script_dir = os.path.dirname(os.path.abspath(__file__));
# 設置當前的路徑為腳本所在的路徑
os.chdir(script_dir);


########## file system ##########
def write_file(path: str, string):
    with open(path, "w+", encoding="utf-8") as file:
        file.write(string);




def read_json(file_path: str):
    with open(file_path, "r", encoding="utf-8") as json_file:
        readed_data = json.load(json_file, strict=False);

    return readed_data;


def write_json(file_path: str, data: Union[dict, list], indent: int = 2):

    json_string = json.dumps(data, indent=indent, ensure_ascii=False)

    with open(file_path, "w+", encoding="utf-8") as json_file:
        json_file.write(json_string);

########## selenium ##########
class Tab:
    FIRST = 0
    NEWEST = -1

def switch_tab(driver, ENUM_TAB: Tab):
    window_handles = driver.window_handles;
    driver.switch_to.window(window_handles[ENUM_TAB])

def open_url(driver, url: str):
    driver.execute_script(f"window.open('{url}', '_blank');");

def scroll_page(driver, value: Union[int, str]):
    driver.execute_script(f"window.scrollTo({str(value)}, document.body.scrollHeight);")

def click(driver, element):
    driver.execute_script("arguments[0].click();", element)



########## string ##########

def sub(input_text: str, pattern: str, replace: str):
    try:
        input_text = re.sub(pattern, replace, input_text);
    except:
        print(f"util.replace 發生例外 text: {input_text}, pattern: {pattern}, replace: {replace}")
        pass;

    return input_text;


########## event_data ##########

### 加工 choice_name
def process_choice_name(choice_name: str):
    ### 替換換行符 ###
    choice_name = sub(choice_name, "\n", "<br>");

    ### 替換半形括號 ###
    choice_name = sub(choice_name, r"\(", "（");
    choice_name = sub(choice_name, r"\)", "）");


    return choice_name;


### 加工 choice_effect
def process_choice_effect(choice_effect: str, process_choice_effect_data: dict, skill_data_jp: dict):
    ### 替換換行符 ###
    choice_effect = sub(choice_effect, "\n", "<br>");

    ### 替換全形正負號 ###
    choice_effect = sub(choice_effect, "＋", "+");
    choice_effect = sub(choice_effect, "－", "-");
    choice_effect = sub(choice_effect, "―", "-");
    choice_effect = sub(choice_effect, "−", "-");
    
    ### 替換半形冒號 ###
    choice_effect = sub(choice_effect, ":", "：");

    ### 替換圈圈符號 ###
    choice_effect = sub(choice_effect, "○", "◯");
    choice_effect = sub(choice_effect, "〇", "◯");

    ### 替換百分比符號 ###
    #出力1000％！
    choice_effect = sub(choice_effect, "%", "％");

    ### 加工 幹勁 ###
    number_pattern = re.compile(r'\d+');

    for yaruki_up in process_choice_effect_data["yaruki"]["up"]:
        number_match = re.search(number_pattern, yaruki_up);
        if number_match:
            number = number_match.group();
            choice_effect = re.sub(rf'{yaruki_up}', rf'<img src="../UmaMisc/Image/Status/yaruki.png"><span class="yaruki">やる気</span>+{number}', choice_effect);
        else:
            choice_effect = re.sub(rf'{yaruki_up}', rf'<img src="../UmaMisc/Image/Status/yaruki.png"><span class="yaruki">やる気</span>+1', choice_effect);
    
    for yaruki_down in process_choice_effect_data["yaruki"]["down"]:
        number_match = re.search(number_pattern, yaruki_down);
        if number_match:
            number = number_match.group();
            choice_effect = re.sub(rf'{yaruki_down}', rf'<img src="../UmaMisc/Image/Status/yaruki.png"><span class="yaruki">やる気</span>-{number}', choice_effect);
        else:
            choice_effect = re.sub(rf'{yaruki_down}', rf'<img src="../UmaMisc/Image/Status/yaruki.png"><span class="yaruki">やる気</span>-1', choice_effect);
    
    ### 加工 技能點 ###
    choice_effect = re.sub(r'スキルPt|スキルpt', rf'<img src="../UmaMisc/Image/Status/skill_point.png"><span class="status_skill_point">スキルPt</span>', choice_effect);
    
    ### 加工 体力 ###
    choice_effect = re.sub(r'体力(?!最大値)', rf'<img src="../UmaMisc/Image/Status/strength.png"><span class="strength">体力</span>', choice_effect);

    ### 加工 体力最大値 ###
    choice_effect = re.sub(r'体力(の)?最大値', r'<img src="../UmaMisc/Image/Status/max_strength.png"><span class="max_strength">体力最大値</span>', choice_effect);

    ### 修正錯誤的技能名稱 ###
    for wrong_word, correct_word in process_choice_effect_data["wrong_word"]["skill_name"].items():
        choice_effect = sub(choice_effect, wrong_word, correct_word);
    
    ### 修正遺漏 ◯ 的技能名稱 ###
    for wrong_word, correct_word in process_choice_effect_data["wrong_word"]["skill_name_has_not_circle"].items():
        choice_effect = re.sub(rf"{wrong_word}(?!◯)", correct_word, choice_effect);

    ### 加工 技能靈感 ###
    for color_v in skill_data_jp.values():
        for rare_v in color_v.values():
            for skill_name in rare_v:
                match = re.search(rf'『?{skill_name}』?(のヒントLv)?', choice_effect)
                if match and match.group(1) != None:
                    choice_effect = re.sub(rf'『?({skill_name})』?(のヒントLv)?', r'<span class="skill_hint">『\1』</span>のヒントLv', choice_effect);
                elif match and match.group(1) == None:
                    choice_effect = re.sub(rf'『?({skill_name})』?(のヒントLv)?', r'<span class="skill_hint">『\1』</span>のヒントLv+1', choice_effect);
    
    ### 加工 +-數字 ###
    choice_effect = re.sub(r"\+\d+(~\d+)?", r'<span class="status_plus_value">\g<0></span>', choice_effect);
    choice_effect = re.sub(r"\-\d+(~\d+)?", r'<span class="status_minus_value">\g<0></span>', choice_effect);

    
    ### 加工 正面狀態 ###
    for plus_condition in process_choice_effect_data["condition"]["plus"]:
        choice_effect = re.sub(rf'(?!<span class="skill_hint">)『({plus_condition})』', r'<span class="plus_condition">『\1』</span>', choice_effect);
    
    ### 加工 負面狀態 ###
    for minus_condition in process_choice_effect_data["condition"]["minus"]:
        choice_effect = re.sub(rf'(?!<span class="skill_hint">)『({minus_condition})』', r'<span class="minus_condition">『\1』</span>', choice_effect);

    ### 加工五種數值 ###
    ## スピード
    choice_effect = re.sub(r"スピード(?!スター)", r'<img src="../UmaMisc/Image/Status/speed.png"><span class="status_speed">\g<0></span>', choice_effect);

    ## スタミナ
    choice_effect = re.sub(r"スタミナ(?!キープ|イーター|グリード)", r'<img src="../UmaMisc/Image/Status/sutamina.png"><span class="status_sutamina">\g<0></span>', choice_effect);

    ## パワー
    # 替換 パワ 為 パワー
    choice_effect = re.sub(r"パワ(?!ー)", "パワー", choice_effect);
    # 進行加工
    choice_effect = re.sub(r"パワー", r'<img src="../UmaMisc/Image/Status/power.png"><span class="status_power">\g<0></span>', choice_effect);

    ## 根性
    choice_effect = re.sub(r"根性", r'<img src="../UmaMisc/Image/Status/konjyou.png"><span class="status_konjyou">\g<0></span>', choice_effect);

    ## 賢さ
    choice_effect = re.sub(r"賢さ", r'<img src="../UmaMisc/Image/Status/kasikosa.png"><span class="status_kasikosa">\g<0></span>', choice_effect);
    return choice_effect;

