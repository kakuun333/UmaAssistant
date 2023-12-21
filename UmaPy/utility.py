import os
import re
import json

##### file #####

def write_json(file_path, json_string):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    # 寫入 event_data_tw.json
    with open(file_path, "w+", encoding="utf-8") as json_file:
        json_file.write(json_string);

def write_convert_data_card(json_string):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    # 寫入 event_data_tw.json
    with open(r"../UmaData/event_data_jp_cvt_tw_card.json", "w+", encoding="utf-8") as json_file:
        json_file.write(json_string);

def write_convert_data_char(json_string):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    # 寫入 event_data_tw.json
    with open(r"../UmaData/event_data_jp_cvt_tw_char.json", "w+", encoding="utf-8") as json_file:
        json_file.write(json_string);

def write_convert_data_skill(json_string):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    # 寫入 event_data_tw.json
    with open(r"../UmaData/skill_data_jp_cvt_tw.json", "w+", encoding="utf-8") as json_file:
        json_file.write(json_string);

def write_file(path, string):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    # 寫入 event_data_tw.json
    with open(path, "w+", encoding="utf-8") as file:
        file.write(string);

def read_json_file(path):
    # 獲取腳本所在的路徑
    script_dir = os.path.dirname(os.path.abspath(__file__));
    # 設置當前的路徑為腳本所在的路徑
    os.chdir(script_dir);

    with open(path, "r", encoding="utf-8") as json_file:
        readed_data = json.load(json_file, strict=False);

    return readed_data;

##### selenium #####

def switch_to_new_tab(driver):
    # 獲取視窗句柄
    window_handles = driver.window_handles;
    # 獲取新視窗句柄
    new_window_handle = window_handles[-1];
    # 切換到新視窗
    driver.switch_to.window(new_window_handle);

def open_url(driver, url):
    driver.execute_script(f"window.open('{url}', '_blank');");

##### string #####

def convert_skill_circle(text):
    # text = text.replace('○', '◯');
    try:
        text = re.sub("○", "◯", text);
    except:
        pass;

    return text;

def convert_nami(text):
    # event_data_jp.json 和 event_data_jp_to_tw_char.json 波浪符不一致，導致「あんし〜ん笹針師、参☆上」無法轉換成中文
    # event_data_jp.json 的波浪〜
    # event_data_jp_to_tw_char.json 的波浪～  
    #
    try:
        text = re.sub("～", "〜", text);
    except:
        pass;

    return text;

def replace(text, original, replace):
    try:
        text = re.sub(original, replace, text);
    except:
        pass;

    return text;

def remove_space(str):
    str = str.replace(" ", "");
    str = str.replace("　", "");
    str = str.replace("\n", "");
    return str;

def return_to_first_window(driver):
    window_handles = driver.window_handles;
    driver.switch_to.window(window_handles[0])