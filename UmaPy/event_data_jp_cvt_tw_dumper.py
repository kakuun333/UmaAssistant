import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By

driver = webdriver.Chrome();


# 全局變數
DEBUG_MODE = False;
event_dict = {};

"""
event_dict = {
    jp_event_owner: {
        "tw_event_owner": tw_event_owner,
        "event_title_dict": {
            jp_event_title: tw_event_title,
            jp_event_title: tw_event_title,
            jp_event_title: tw_event_title,
            ......
        }
    },
    jp_event_owner: {
        "tw_event_owner": tw_event_owner,
        "event_title_dict": {
            jp_event_title: tw_event_title,
            jp_event_title: tw_event_title,
            jp_event_title: tw_event_title,
            ......
        }
    },
    ......
}
"""



def filtered_card_img_list(img_list):
    filtered_img_list = [];

    pattern = r"Support thumb \d+.png";

    for img in img_list:
        if (re.match(pattern, img.get_attribute("alt")) != None):
            filtered_img_list.append(img);
    
    return filtered_img_list;

def filtered_char_img_list(img_list):
    filtered_img_list = [];

    pattern = r"Chr icon";

    for img in img_list:
        if (re.match(pattern, img.get_attribute("alt")) != None):
            filtered_img_list.append(img);
    
    return filtered_img_list;



def open_char_card_url(img):
    # 找到 img 的父級元素
    a = img.find_element(By.XPATH, '..');
    # 獲取 url
    url = a.get_attribute("href");

    driver.execute_script(f"window.open('{url}', '_blank');");



def get_tw_card_event_owner():
    main_element = driver.find_element(By.CLASS_NAME, "support_card-right");

    # another_name
    another_name_element = main_element.find_element(By.XPATH, ".//b");
    another_name_pattern = r"【(.+)】";
    another_name = re.match(another_name_pattern, another_name_element.text).group(1);

    # name
    font = main_element.find_element(By.TAG_NAME, "font");
    name_element = font.find_element(By.TAG_NAME, "big");

    name = utility.remove_space(name_element.text);

    tw_event_owner = name + "（" + another_name + "）";

    print("tw_event_owner: " + tw_event_owner);
    
    return tw_event_owner;

def get_event_title_dict():
    dict = {};

    title_pattern = r".+/(.+)";

    divs = driver.find_elements(By.CLASS_NAME, "sj-an");
    for div in divs:
        a = div.find_element(By.XPATH, ".//a");
        title = a.get_attribute("title");

        title = utility.remove_space(title);
        if (title != None and '/' in title and a.text):
            try:
                jp_event_title = re.match(title_pattern, title).group(1);
            except:
                jp_event_title = "【遺失】"
                
            tw_event_title = a.text

            dict[jp_event_title] = tw_event_title;
            print("jp_title: " + jp_event_title + "  tw_title: " + tw_event_title);


    return dict;

def get_event_title_list():
    list = [];


    divs = driver.find_elements(By.CLASS_NAME, "sj-an");
    for div in divs:
        try:
            a = div.find_element(By.XPATH, ".//a");
            title = a.get_attribute("title");

            title = utility.remove_space(title);
            # if (title != None and '/' in title and a.text):
            if (title != None and a.text): # 有些 title 沒有 '/' 就會造成無限迴圈
                                           # https://wiki.biligame.com/umamusume/%E3%80%90%E7%89%B9%E9%9B%B7%E6%A3%AE%E5%AD%B8%E5%9C%92%E3%80%91%E9%B6%B4%E4%B8%B8%E5%BC%B7%E5%BF%97

                event_title = a.text

                event_title = utility.convert_nami(event_title);

                event_title = utility.replace(event_title, "·", "・");

                event_title = utility.replace(event_title, "＃", "#");

                event_title = utility.replace(event_title, "／", "/");

                event_title = utility.replace(event_title, "　", "");

                event_title = utility.replace(event_title, "〜", "～");

                event_title = utility.replace(event_title, "―", "ー"); # 信仰心と親切心が交わる時ーー

                print("event_title: " + event_title);

                list.append(event_title);
        except:
            pass;


    return list;


def get_jp_card_event_owner():
    jp_event_owner = "";

    pattern = re.compile("【(.+)】(.+)");

    div = driver.find_element(By.CLASS_NAME, "map-dh-right");
    a_elements = div.find_elements(By.XPATH, ".//a");
    for a in a_elements:
        span = a.find_element(By.CLASS_NAME, "map-dh-an");
        if (span.text == "日服"):
            jp_event_owner = a.get_attribute("title");

            jp_event_owner = re.sub(pattern, r"\2（\1）", jp_event_owner)

    print("jp_event_owner: " + jp_event_owner);
    return jp_event_owner;

def get_tw_char_event_owner():
    a = driver.find_element(By.CSS_SELECTOR, ".mw-selflink.selflink");

    pattern = re.compile("【(.+)】(.+)");

    tw_char_event_owner = re.sub(pattern, r"\2（\1）", a.text);

    tw_char_event_owner = utility.replace("繁/米浴（Make up Vampire!）", "米浴（Make up Vampire!）")

    print(tw_char_event_owner);

    return tw_char_event_owner;

def open_jp_url():
    span = driver.find_element(By.CLASS_NAME, "map-dh-an");
    if (span.text == "日服"):
        a = span.find_element(By.XPATH, "..");
        url = a.get_attribute("href");
        driver.execute_script(f"window.open('{url}', '_blank');");

def get_jp_char_event_owner():
    table_list = driver.find_elements(By.CLASS_NAME, "wikitable");
    tbody = table_list[0].find_element(By.XPATH, ".//tbody");
    tr_list = tbody.find_elements(By.XPATH, ".//tr");
    td_list = tr_list[1].find_elements(By.XPATH, ".//td");
    name = utility.remove_space(td_list[1].text);
    another_name = utility.remove_space(td_list[2].text);
    jp_char_event_owner = name + "（" + another_name + "）";

    print(jp_char_event_owner);
    
    return jp_char_event_owner;


def list_to_dict(jp_event_title_list, tw_event_title_list):
    dict = {};

    for i in range(len(jp_event_title_list)):
        try:
            dict[jp_event_title_list[i]] = tw_event_title_list[i];
        except:
            print("[警告] tw_event_title_list 超出索引範圍！");

    return dict;

def dump_card_convert_data():
    driver.get("https://wiki.biligame.com/umamusume/%E7%B9%81%E4%B8%AD%E6%94%AF%E6%8F%B4%E5%8D%A1%E4%B8%80%E8%A7%88");
    time.sleep(5);
    img_list = driver.find_elements(By.TAG_NAME, "img");
    for img in filtered_card_img_list(img_list):
        # img.click();
        open_char_card_url(img);

        utility.switch_to_new_tab(driver);

        tw_event_owner = get_tw_card_event_owner();
        jp_event_owner = get_jp_card_event_owner();

        # event_title_dict = get_event_title_dict();


        got_tw_list = False;
        tw_event_title_list = [];
        while (not got_tw_list):
            tw_event_title_list = get_event_title_list();
            if (len(tw_event_title_list) != 0):
                got_tw_list = True;
            time.sleep(0.25);

        open_jp_url();

        utility.switch_to_new_tab(driver);

        got_jp_list = False;
        jp_event_title_list = [];
        while (not got_jp_list):
            jp_event_title_list = get_event_title_list();
            if (len(jp_event_title_list) != 0):
                got_jp_list = True;
            time.sleep(0.25);
        
        event_title_dict = list_to_dict(jp_event_title_list, tw_event_title_list);


        event_dict[jp_event_owner] = {
            "tw_event_owner": tw_event_owner,
            "event_title_dict": event_title_dict,
        }

        json_string = json.dumps(event_dict, indent=2, ensure_ascii=False)

        utility.write_convert_data_card(json_string);

        driver.close();

        utility.switch_to_new_tab(driver);

        driver.close();

        utility.return_to_first_window(driver);




def dump_char_convert_data():
    # https://wiki.biligame.com/umamusume/%E3%80%90%E7%89%B9%E9%9B%B7%E6%A3%AE%E5%AD%B8%E5%9C%92%E3%80%91%E9%B6%B4%E4%B8%B8%E5%BC%B7%E5%BF%97
    driver.get("https://wiki.biligame.com/umamusume/%E7%B9%81%E4%B8%AD%E8%B5%9B%E9%A9%AC%E5%A8%98%E4%B8%80%E8%A7%88");
    time.sleep(6);
    img_list = driver.find_elements(By.TAG_NAME, "img");
    for img in filtered_char_img_list(img_list):
        open_char_card_url(img);

        utility.switch_to_new_tab(driver);

        tw_char_event_owner = get_tw_char_event_owner();

        # time.sleep(1.5);

        got_tw_list = False;
        tw_event_title_list = [];
        while (not got_tw_list):
            tw_event_title_list = get_event_title_list();
            if (len(tw_event_title_list) != 0):
                got_tw_list = True;
            time.sleep(0.25);

        open_jp_url();

        utility.switch_to_new_tab(driver);

        jp_char_event_owner = get_jp_char_event_owner();

        got_jp_list = False;
        jp_event_title_list = [];
        while (not got_jp_list):
            jp_event_title_list = get_event_title_list();
            if (len(jp_event_title_list) != 0):
                got_jp_list = True;
            time.sleep(0.25);

        event_title_dict = list_to_dict(jp_event_title_list, tw_event_title_list);

        event_dict[jp_char_event_owner] = {
            "tw_event_owner": tw_char_event_owner,
            "event_title_dict": event_title_dict,
        }

        json_string = json.dumps(event_dict, indent=2, ensure_ascii=False)

        utility.write_convert_data_char(json_string);

        driver.close();

        utility.switch_to_new_tab(driver);

        driver.close();

        utility.return_to_first_window(driver);


# 獲取支援卡資料
dump_card_convert_data();

# 獲取角色資料
dump_char_convert_data();



























# driver.get("https://wiki.biligame.com/umamusume/%E3%80%90%E7%89%B9%E9%9B%B7%E6%A3%AE%E5%AD%B8%E5%9C%92%E3%80%91%E9%B6%B4%E4%B8%B8%E5%BC%B7%E5%BF%97");
# time.sleep(6);

# tw_event_owner = get_tw_card_event_owner();
# jp_event_owner = get_jp_card_event_owner();

# event_title_dict = get_event_title_dict();


# got_tw_list = False;
# tw_event_title_list = [];
# while (not got_tw_list):
#     tw_event_title_list = get_event_title_list();
#     if (len(tw_event_title_list) != 0):
#         got_tw_list = True;
#     time.sleep(0.25);

# open_jp_url();

# utility.switch_to_new_tab(driver);

# got_jp_list = False;
# jp_event_title_list = [];
# while (not got_jp_list):
#     jp_event_title_list = get_event_title_list();
#     if (len(jp_event_title_list) != 0):
#         got_jp_list = True;
#     time.sleep(0.25);

# event_title_dict = list_to_dict(jp_event_title_list, tw_event_title_list);


# event_dict[jp_event_owner] = {
#     "tw_event_owner": tw_event_owner,
#     "event_title_dict": event_title_dict,
# }

# json_string = json.dumps(event_dict, indent=2, ensure_ascii=False)

# utility.write_convert_data_card(json_string);


