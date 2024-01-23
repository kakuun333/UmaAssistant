import os
import re
import json
from typing import Union

# 獲取腳本所在的路徑
script_dir = os.path.dirname(os.path.abspath(__file__));
# 設置當前的路徑為腳本所在的路徑
os.chdir(script_dir);


########## file system ##########
def write_file(path, string):
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


########## string ##########

def sub(input_text: str, pattern: str, replace: str):
    try:
        input_text = re.sub(pattern, replace, input_text);
    except:
        print(f"util.replace 發生例外 text: {input_text}, pattern: {pattern}, replace: {replace}")
        pass;

    return input_text;