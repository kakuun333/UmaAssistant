import os
import re
import time
import util
from selenium import webdriver
from selenium.webdriver.common.by import By
import urllib.request


driver = webdriver.Chrome();

# # 獲取腳本所在的路徑
# script_dir = os.path.dirname(os.path.abspath(__file__));
# # 設置當前的路徑為腳本所在的路徑
# os.chdir(script_dir);
save_char_icon_path = r"../UmaMisc/Image/Character"


select_character_list = [];

"""
select_character_list = [
    {
        "jp_event_owner": "小笠帽",
        "tw_event_owner": "オグリキャップ（スタービートライト）",
        "icon": "i_5.png"
    },
    {
        "jp_event_owner": "小笠帽",
        "tw_event_owner": "オグリキャップ（スタービートライト）",
        "icon": "i_5.png"
    }
]
"""

def get_char_name():
    div = driver.find_element(By.CSS_SELECTOR, ".article-top.in-article");

    h1 = div.find_element(By.CLASS_NAME, "_title");

    matched_string = "";

    # 【ウマ娘】ゴールドシップ(星2)の評価とイベント
    pattern = r"【ウマ娘】(.+)\(.+\)";
    try:
        matched_string = re.match(pattern, h1.text).group(1);
    except:
        pass;

    return matched_string;

def get_char_another_name():
    char_another_name = "";

    th_list = driver.find_elements(By.TAG_NAME, "th");

    for th in th_list:
        if (th.text == "名称"):
            parent_tr = th.find_element(By.XPATH, '..');
            target_td = parent_tr.find_element(By.XPATH, ".//td");
            char_another_name = target_td.text;

    return char_another_name;


def open_char_url(element):
    # 找到 element 的父級元素
    a = element.find_element(By.XPATH, '..');
    # 獲取 url
    url = a.get_attribute("href");

    driver.execute_script(f"window.open('{url}', '_blank');");

def dump_char_data(dump_icon):
    driver.get("https://gamewith.jp/uma-musume/article/show/253241");
    time.sleep(6);

    umamusume_ikusei_ichiran = driver.find_element(By.CLASS_NAME, "umamusume-ikusei-ichiran");
    img_list = umamusume_ikusei_ichiran.find_elements(By.XPATH, ".//img");

    icon_number_pattern = r"https://img.gamewith.jp/article_tools/uma-musume/gacha/i_([0-9]+).png"

    for img in img_list:
        try:
            img_url = img.get_attribute("data-original"); # WTF;
            matched_icon_number = re.match(icon_number_pattern, img_url).group(1)

            ##### 下載圖片 #####

            print(f"matched_icon_number: {matched_icon_number}");

            if (dump_icon):
                save_path = os.path.join(save_char_icon_path, f"i_{matched_icon_number}.png");
                urllib.request.urlretrieve(img_url, save_path);

            char_data_dict = {};

            open_char_url(img);

            util.switch_tab(driver, util.Tab.NEWEST);
            
            char_name = get_char_name();
            char_name = util.sub(char_name, "水着", "");

            print("char_name: ", char_name);

            char_another_name = get_char_another_name();

            print("char_another_name: ", char_name);
        
            char_data_dict["icon"] = f"i_{matched_icon_number}.png";
            char_data_dict["jp_event_owner"] = f"{char_name}（{char_another_name}）";
            char_data_dict["tw_event_owner"] = None;

            select_character_list.append(char_data_dict);

            util.write_json("../UmaData/select_character_data.json", select_character_list);

            driver.close();

            util.switch_tab(driver, util.Tab.FIRST);
        except:
            pass;




dump_char_data(dump_icon=True);