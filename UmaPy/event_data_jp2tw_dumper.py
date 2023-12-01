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
skill_dict = {};
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

def switch_to_new_tab():
    # 獲取視窗句柄
    window_handles = driver.window_handles;
    # 獲取新視窗句柄
    new_window_handle = window_handles[-1];
    # 切換到新視窗
    driver.switch_to.window(new_window_handle);

def open_char_card_url(img):
    # 找到 img 的父級元素
    a = img.find_element(By.XPATH, '..');
    # 獲取 url
    url = a.get_attribute("href");

    driver.execute_script(f"window.open('{url}', '_blank');");

def open_url(url):
    driver.execute_script(f"window.open('{url}', '_blank');");

def return_to_first_window():
    window_handles = driver.window_handles;
    driver.switch_to.window(window_handles[0])

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

        switch_to_new_tab();

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

        switch_to_new_tab();

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

        switch_to_new_tab();

        driver.close();

        return_to_first_window();




def dump_char_convert_data():
    # https://wiki.biligame.com/umamusume/%E3%80%90%E7%89%B9%E9%9B%B7%E6%A3%AE%E5%AD%B8%E5%9C%92%E3%80%91%E9%B6%B4%E4%B8%B8%E5%BC%B7%E5%BF%97
    driver.get("https://wiki.biligame.com/umamusume/%E7%B9%81%E4%B8%AD%E8%B5%9B%E9%A9%AC%E5%A8%98%E4%B8%80%E8%A7%88");
    time.sleep(6);
    img_list = driver.find_elements(By.TAG_NAME, "img");
    for img in filtered_char_img_list(img_list):
        open_char_card_url(img);

        switch_to_new_tab();

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

        switch_to_new_tab();

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

        switch_to_new_tab();

        driver.close();

        return_to_first_window();



def get_jp_skill_title():
    jp_skill_title = "";

    span = driver.find_element(By.CLASS_NAME, "map-dh-an");
    if (span.text == "日服"):
        a_span = span.find_element(By.XPATH, "..");
        jp_skill_title = a_span.get_attribute("title");

        print(jp_skill_title);
    return jp_skill_title;

def get_tw_skill_title():
    tw_skill_title = "";

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    th = wikitable.find_element(By.TAG_NAME, "th");

    tw_skill_title = re.match(r"(.+).+/.+", th.text).group(1);

    print(tw_skill_title);

    return tw_skill_title;

def get_tw_skill_effect():
    tw_skill_effect = "";

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    tr = wikitable.find_elements(By.XPATH, ".//tr")[5];

    td = tr.find_element(By.TAG_NAME, "td");

    tw_skill_effect = td.text;

    print(tw_skill_effect);

    return tw_skill_effect;

def get_tw_upper_skill():
    tw_upper_skill = None;

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    tr = wikitable.find_elements(By.XPATH, ".//tr")[17];
    try:
        font = tr.find_element(By.XPATH, ".//font");
        print("tw_upper_skill: " + font.text);
        tw_upper_skill = font.text;
    except:
        pass;

    return tw_upper_skill;

def get_tw_lower_skill():
    tw_lower_skill = None;

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    tr = wikitable.find_elements(By.XPATH, ".//tr")[16];
    try:
        font = tr.find_element(By.XPATH, ".//font");
        print("tw_lower_skill: " + font.text);
        tw_lower_skill = font.text;
    except:
        pass;

    return tw_lower_skill;

def convert_circle(text):
    # text = text.replace('○', '◯');
    try:
        text = re.sub("○", "◯", text);
    except:
        pass;

    return text;

def dump_skill_convert_data():
    driver.get("https://wiki.biligame.com/umamusume/%E7%B9%81%E4%B8%AD%E6%8A%80%E8%83%BD%E9%80%9F%E6%9F%A5%E8%A1%A8");
    time.sleep(6);

    skill_list = driver.find_elements(By.CLASS_NAME, "divsort");
    for skill in skill_list:
        td_list = skill.find_elements(By.XPATH, ".//td");

        try:
            if (td_list[3].text == "普通" or td_list[3].text == "传说"):
                a = td_list[0].find_element(By.XPATH, ".//a");
                skill_url = a.get_attribute("href");
                open_url(skill_url);
                switch_to_new_tab();
                jp_skill_title = get_jp_skill_title();
                jp_skill_title = convert_circle(jp_skill_title);

                tw_skill_title = get_tw_skill_title();
                tw_skill_title = convert_circle(tw_skill_title);

                tw_skill_effect = get_tw_skill_effect();
                tw_skill_effect = convert_circle(tw_skill_effect);
        
                tw_upper_skill = get_tw_upper_skill();
                tw_upper_skill = convert_circle(tw_upper_skill);

                tw_lower_skill = get_tw_lower_skill();
                tw_lower_skill = convert_circle(tw_lower_skill);

                skill_dict[jp_skill_title] = {
                    "tw_skill_title": tw_skill_title,
                    "tw_skill_effect": tw_skill_effect,
                    "tw_upper_skill": tw_upper_skill,
                    "tw_lower_skill": tw_lower_skill
                }

                json_string = json.dumps(skill_dict, indent=2, ensure_ascii=False)

                utility.write_convert_data_skill(json_string);

                driver.close();

                return_to_first_window();
        except:
            return_to_first_window();
            pass;

dump_skill_convert_data();

# dump_card_convert_data();
# dump_char_convert_data();



























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

# switch_to_new_tab();

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


