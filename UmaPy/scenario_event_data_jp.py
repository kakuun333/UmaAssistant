import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By

driver = webdriver.Chrome();


scenario_event_dict = {
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

jp_status_name_list = {
    "スピード",
    "スタミナ",
    "パワー",
    "根性",
    "賢さ",
}

status_class_dict = {
    "スピード": "speed",
    "スタミナ": "sutamina",
    "パワー": "power",
    "根性": "konjyou",
    "賢さ": "kasikosa",
}




def add_tag_to_choice_effect(choice_effect):
    choice_effect = re.sub(r"(\-\d+[~\d+]*)", r'<span class="status_minus_value">\1</span>', choice_effect)
    choice_effect = re.sub(r"(\+\d+[~\d+]*)", r'<span class="status_plus_value">\1</span>', choice_effect)

    # <span class=\"skill_hint\">『"..skill.."』</span>
    choice_effect = re.sub(r"『(.+)』", r'<span class="skill_hint">『\1』</span>', choice_effect)

    for status_name in jp_status_name_list:
        
        replace_pattern = rf'<img src="../UmaMisc/Image/Status/{status_class_dict[status_name]}.png"><span class="status_{status_class_dict[status_name]}">\1</span>'
        # choice_effect = string.gsub(choice_effect, "("..status_name..")", replace_pattern);

        choice_effect = re.sub(rf"({status_name}?!キープ)", replace_pattern, choice_effect)


    return choice_effect;


def get_scenario_event_data_jp(scenario_type):
    event_title_list = [];  #161
    choice_list = [];       #161
    h3_list = driver.find_elements(By.TAG_NAME, "h3");
    div_choice_list = driver.find_elements(By.CLASS_NAME, "uma_choice_table");
    
    for h3 in h3_list:
        event_title = h3.text;
        # print(event_title)
        event_title_list.append(event_title);
        
    for choice_element in div_choice_list:
        tr_list = choice_element.find_elements(By.TAG_NAME, "tr");

        choice = [];

        for tr in tr_list:
            choice_title_element = tr.find_element(By.XPATH, ".//th");
            choice_title = choice_title_element.text;
            choice_effect_element = tr.find_element(By.XPATH, ".//td");
            choice_effect = choice_effect_element.text;

            choice_effect = add_tag_to_choice_effect(choice_effect);

            # 替換 ScenarioStatus
            # グラライ ScenarioStatus
            choice_effect = re.sub(r'ダンス', rf'<img src="../UmaMisc/Image/ScenarioStatus/performance_Da.png">ダンス', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'ボーカル', rf'<img src="../UmaMisc/Image/ScenarioStatus/performance_Vo.png">ボーカル', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'パッション', rf'<img src="../UmaMisc/Image/ScenarioStatus/performance_Pa.png">パッション', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'ビジュアル', rf'<img src="../UmaMisc/Image/ScenarioStatus/performance_Vi.png">ビジュアル', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'メンタル', rf'<img src="../UmaMisc/Image/ScenarioStatus/performance_Me.png">メンタル', choice_effect, flags=re.IGNORECASE);

            choice_effect = utility.replace(choice_effect, "\n", "<br>");

            choice_info = {
                "choice_title": choice_title,
                "choice_effect": choice_effect,
            }


            choice.append(choice_info);

        choice_list.append(choice);

    for event_title, choice in zip(event_title_list, choice_list):
        scenario_event_dict[scenario_type][event_title] = choice;


def dump_scenario_event_data_jp():
    # アオハル
    driver.get("https://gamewith.jp/uma-musume/article/show/292841");
    utility.switch_to_new_tab(driver);
    get_scenario_event_data_jp("aoharu");
    # メイクラ
    driver.get("https://gamewith.jp/uma-musume/article/show/320396");
    utility.switch_to_new_tab(driver);
    get_scenario_event_data_jp("meikura");
    # グラライ 
    driver.get("https://gamewith.jp/uma-musume/article/show/360338");
    utility.switch_to_new_tab(driver);
    get_scenario_event_data_jp("gurarai");
    # グラマス
    # scenario_event_dict["guramasu"]["今を駆ける者たちの祖"] = {
    #     1: {
    #         "choice_title": "ダーレーアラビアン",
    #         "choice_effect": "全ステータス+10、スキルPt+40<br>太陽の叡智のヒント+Lv1"
    #     },
    # }



dump_scenario_event_data_jp();


json_string = json.dumps(scenario_event_dict, indent=2, ensure_ascii=False);
utility.write_file("../UmaData/scenario_event_data_jp.json", json_string);