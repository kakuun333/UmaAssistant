import os
import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC



driver = webdriver.Chrome();

# skill_data_jp = utility.read_json_file(r"../UmaData/skill_data_jp.json");

enhance_skill_data_dict = {}

"""
enhance_skill_data_dict = {
    skill_name = {
        skill_effect_title: skill_effect_data,
        skill_effect_title: skill_effect_data,
        skill_effect_title: skill_effect_data,
        ...
    }    
}
"""

CONDITION_CARD_DIV_INDEX = 1;
EFFECT_CARD_DIV_INDEX = 2;

SKILL_CHECKBOX_DIV_CLASS_NAME = "checkboxGroup_component_checkboxGroup__body__LeA_L";
SKILL_TABLE_DIV_CLASS_NAME = "skillTable_component_skillTable__1n_1S";
DETAIL_CARD_DIV_CLASS_NAME = "descriptionCardSection_component_descriptionCardSection__kviO4";
DETAIL_CARD_INFO_DIV_CLASS_NAME = "descriptionCardSection_component_descriptionCardSection__body__BFZUJ";

CARD_TITLE_CLASS_NAME = "labelLine_component_labelLine__label__P9lqy";
CARD_DATA_CLASS_NAME = "labelLine_component_labelLine__body__8HMzQ";

SKILL_NAME_DIV_CLASS_NAME = "skillCard_component_skillCard__name__0mf6m";


def click_checkbox_list_by_class(class_name):
    skill_div_list = driver.find_elements(By.CLASS_NAME, class_name);

    for div_idx, skill_div in enumerate(skill_div_list):
        if (div_idx > 4): break;

        skill_checkbox_list = skill_div.find_elements(By.XPATH, ".//label");

        for idx, checkbox_div in enumerate(skill_checkbox_list):
            if (div_idx < 4):
                checkbox_div.click();
            elif (div_idx == 4):    
                if (idx <= 1):
                    checkbox_div.click();

# def repeat_find_element(by_type, by_value):
#     element = None;
#     try:
#         element = driver.find_element(by_type, by_value);
#         return element;
#     except:
#         print("except")
#         repeat_find_element(by_type, by_value);


def get_skill_info():
    

    # 等待最多 10秒 直到指定的元素可見
    # skill_name_div = WebDriverWait(driver, 10).until(
    #     EC.presence_of_element_located((By.CLASS_NAME, SKILL_NAME_DIV_CLASS_NAME))
    # )

    # https://xn--gck1f423k.xn--1bvt37a.tools/skills/202031


    skill_name_div = driver.find_element(By.CLASS_NAME, SKILL_NAME_DIV_CLASS_NAME);

    
    skill_name = None;

    try:
        skill_name = skill_name_div.text;
    except:
        while (skill_name == None):
            skill_name = driver.find_element(By.CLASS_NAME, SKILL_NAME_DIV_CLASS_NAME).text;
            print("waiting")
            driver.implicitly_wait(0.5);

    skill_name = utility.replace(skill_name, "○", "◯");

    print(skill_name);

    enhance_skill_data_dict[skill_name] = {
        "skill_effect": {},
        "skill_condition": {},
    };


    # 獲取 skill_effect
    detail_card_div_list = driver.find_elements(By.CLASS_NAME, DETAIL_CARD_DIV_CLASS_NAME);
    effect_card_div = detail_card_div_list[EFFECT_CARD_DIV_INDEX];
    effect_card_info_div = effect_card_div.find_element(By.CLASS_NAME, DETAIL_CARD_INFO_DIV_CLASS_NAME);
    labelLine_div_list = effect_card_info_div.find_elements(By.TAG_NAME, "div");

    for labelLine_div in labelLine_div_list:
        
        try:
            skill_effect_title = labelLine_div.find_element(By.CLASS_NAME, CARD_TITLE_CLASS_NAME).text;
            skill_effect_data = labelLine_div.find_element(By.CLASS_NAME, CARD_DATA_CLASS_NAME).text;

            if (skill_effect_data == "-"):
                skill_effect_data = None;
            
            enhance_skill_data_dict[skill_name]["skill_effect"][skill_effect_title] = skill_effect_data;

        except:
            print("passed");
            pass;
    
    # 獲取 skill_condition
    detail_card_div_list = driver.find_elements(By.CLASS_NAME, DETAIL_CARD_DIV_CLASS_NAME);
    condition_card_div = detail_card_div_list[CONDITION_CARD_DIV_INDEX];
    condition_card_info_div = condition_card_div.find_element(By.CLASS_NAME, DETAIL_CARD_INFO_DIV_CLASS_NAME);
    labelLine_div_list = condition_card_info_div.find_elements(By.TAG_NAME, "div");

    for labelLine_div in labelLine_div_list:
        try:
            skill_condition_title = labelLine_div.find_element(By.CLASS_NAME, CARD_TITLE_CLASS_NAME).text;
            skill_condition_data = labelLine_div.find_element(By.CLASS_NAME, CARD_DATA_CLASS_NAME).text;

            print(skill_condition_title, skill_condition_data)

            # if (skill_condition_data == "-"):
            #     skill_condition_data = None;
            
            enhance_skill_data_dict[skill_name]["skill_condition"][skill_condition_title] = skill_condition_data;

        except:
            print("passed");
            pass;

    json_string = json.dumps(enhance_skill_data_dict, indent=2, ensure_ascii=False)
    utility.write_json(r"../UmaData/enhance_skill_data_jp.json", json_string);





def dump_enhance_skill_data():
    driver.get("https://ウマ娘.攻略.tools/skills");
    time.sleep(3);
    driver.execute_script("window.scrollTo(500, document.body.scrollHeight);")
    time.sleep(3);



    click_checkbox_list_by_class(SKILL_CHECKBOX_DIV_CLASS_NAME);

    skill_table_div = driver.find_element(By.CLASS_NAME, SKILL_TABLE_DIV_CLASS_NAME);
    skill_a_list = skill_table_div.find_elements(By.TAG_NAME, "a");
    for skill_a in skill_a_list:
        skill_url = skill_a.get_attribute("href");

        utility.open_url(driver, skill_url);

        utility.switch_to_new_tab(driver);

        get_skill_info();

        driver.close();

        utility.switch_to_new_tab(driver);

    time.sleep(20);

dump_enhance_skill_data();

# driver.get("https://xn--gck1f423k.xn--1bvt37a.tools/skills/202031");
# get_skill_info();