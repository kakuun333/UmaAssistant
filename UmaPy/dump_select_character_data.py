import os
import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By
import urllib.request


driver = webdriver.Chrome();

# 獲取腳本所在的路徑
script_dir = os.path.dirname(os.path.abspath(__file__));
# 設置當前的路徑為腳本所在的路徑
os.chdir(script_dir);
save_folder = r"../UmaMisc/Image/Character"


select_character_list = [];

"""
select_character_list = {
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
}
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
    img_list = driver.find_elements(By.TAG_NAME, "img");

    for img in img_list:
        # https://img.gamewith.jp/article_tools/uma-musume/gacha/i_48.png
        pattern = r"https://img.gamewith.jp/article_tools/uma-musume/gacha/i_([0-9]+).png"

        img_url = img.get_attribute("data-original");

        try:
            matched_string = re.match(pattern, img_url).group(1)

            ##### 下載圖片 #####
            if (dump_icon):
                print(f"matched_string: {matched_string}");
                save_path = os.path.join(save_folder, f"i_{matched_string}.png");
                urllib.request.urlretrieve(img_url, save_path);

            # json
            tmp_dict = {};

            open_char_url(img);

            utility.switch_to_new_tab(driver);

            char_name = get_char_name();
            char_another_name = get_char_another_name();
        
            tmp_dict["icon"] = f"i_{matched_string}.png";
            tmp_dict["jp_event_owner"] = f"{char_name}（{char_another_name}）";
            tmp_dict["tw_event_owner"] = None;

            select_character_list.append(tmp_dict);

            json_string = json.dumps(select_character_list, indent=2, ensure_ascii=False)
            utility.write_json(r"../UmaData/select_character_data.json", json_string);

            driver.close();

            utility.return_to_first_window(driver);

        except:
            pass;




dump_char_data(dump_icon=True);