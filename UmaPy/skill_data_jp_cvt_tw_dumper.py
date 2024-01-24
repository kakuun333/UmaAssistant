import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By

driver = webdriver.Chrome();


skill_dict = {};



def get_jp_skill_name():
    jp_skill_name = "";

    span = driver.find_element(By.CLASS_NAME, "map-dh-an");
    if (span.text == "日服"):
        a_span = span.find_element(By.XPATH, "..");
        jp_skill_name = a_span.get_attribute("title");

        print(jp_skill_name);
    return jp_skill_name;

def get_tw_skill_name():
    tw_skill_name = "";

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    th = wikitable.find_element(By.TAG_NAME, "th");

    tw_skill_name = re.match(r"(.+).+/.+", th.text).group(1);

    print(tw_skill_name);

    return tw_skill_name;

def get_tw_skill_description():
    tw_skill_description = "";

    wikitable = driver.find_element(By.CLASS_NAME, "wikitable");
    tr = wikitable.find_elements(By.XPATH, ".//tr")[5];

    td = tr.find_element(By.TAG_NAME, "td");

    tw_skill_description = td.text;

    print(tw_skill_description);

    return tw_skill_description;

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
                utility.open_url(driver, skill_url);
                utility.switch_to_new_tab(driver);
                jp_skill_name = get_jp_skill_name();
                jp_skill_name = utility.replace(jp_skill_name, "○", "◯");

                tw_skill_name = get_tw_skill_name();
                tw_skill_name = utility.replace(tw_skill_name, "○", "◯");

                tw_skill_description = get_tw_skill_description();
                tw_skill_description = utility.replace(tw_skill_description, "○", "◯");
        
                tw_upper_skill = get_tw_upper_skill();
                tw_upper_skill = utility.replace(tw_upper_skill, "○", "◯");

                tw_lower_skill = get_tw_lower_skill();
                tw_lower_skill = utility.replace(tw_lower_skill, "○", "◯");

                skill_dict[jp_skill_name] = {
                    "tw_skill_name": tw_skill_name,
                    "tw_skill_description": tw_skill_description,
                    "tw_upper_skill": tw_upper_skill,
                    "tw_lower_skill": tw_lower_skill
                }

                json_string = json.dumps(skill_dict, indent=2, ensure_ascii=False)

                utility.write_convert_data_skill(json_string);

                driver.close();

                utility.return_to_first_window(driver);
        except:
            utility.return_to_first_window(driver);
            pass;

dump_skill_convert_data();