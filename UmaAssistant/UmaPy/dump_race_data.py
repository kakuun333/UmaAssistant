# std
import os
import re
import time
import urllib.request

# 3rdparty
from selenium import webdriver
from selenium.webdriver.common.by import By

# src
import util
from umaenum import *
from umaglobal import *


driver = webdriver.Chrome();

race_data_jp: list = [];# util.read_json("../UmaData/race_data_jp.json");

SAVE_RACE_IMAGE_PATH = r"../UmaMisc/Image/Race"

def dump_race_data_jp(is_dump_icon: bool):
    driver.get(DataUrl.JP_ALL_RACE_LIST);

    time.sleep(6);

    sort_element_filter = driver.find_element(By.CLASS_NAME, "sort_element_filter");
    tr_race_item_list = sort_element_filter.find_elements(By.XPATH, ".//tr");


    TOTAL_COUNT = len(tr_race_item_list);
    current_count = 0;
    for race_item in tr_race_item_list:
        util.scroll_info_view(driver, race_item);
        current_count += 1;

        if race_item.get_attribute("data-col1") == None: continue;

        race_info_obj = {
            "race_name": "",
            "race_grade": "",
            "race_track": "",
            "racecourse": "",
            "race_distance": "",
            "race_distance_type": "",
            "race_direction": "",

            # date
            "race_date_grade": "",
            "race_date_day": "",

            # img
            "race_image_name": "",
        }

        td_list = race_item.find_elements(By.TAG_NAME, "td");

        ##### IMAGE
        image_url: str = td_list[0].find_element(By.XPATH, ".//img").get_attribute("src");

        # date_info_match = re.search(r"([0-9]年目) (.+)", original_date_info);
        # "https://img.gamewith.jp/article_tools/uma-musume/gacha/i_race2.png"
        img_name_match = re.search(r"i_(.+[0-9]+).png", image_url);

        if img_name_match:
            image_name = f"i_{img_name_match.group(1)}.png";

            race_info_obj["race_image_name"] = image_name;
            ##### 下載圖片 #####
            if (is_dump_icon):
                save_path = os.path.join(SAVE_RACE_IMAGE_PATH, image_name);
                urllib.request.urlretrieve(image_url, save_path);
        else:
            print(img_name_match);
        
        # dump date_info
        original_date_info =  td_list[0].text;
        date_info_match = re.search(r"([0-9]年目) (.+)", original_date_info);
        if date_info_match:
            date_grade = date_info_match.group(1);
            if date_grade == "1年目": date_grade = "ジュニア"
            elif date_grade == "2年目": date_grade = "クラシック"
            elif date_grade == "3年目": date_grade = "シニア"

            date_day = date_info_match.group(2);
        
            race_info_obj["race_date_grade"] = date_grade;
            race_info_obj["race_date_day"] = date_day;
            # print(f"date_grade: {date_grade}, date_day: {date_day}");
        # dump race_info
        original_race_info = td_list[1].text; # ききょうステークス/OP/阪神芝/1400m(短距離)/右内

        original_race_info = re.sub(r"ジュニア|クラシック|シニア|外|内", "", original_race_info);

        original_race_info = original_race_info.replace(" ", "");
        original_race_info = original_race_info.replace("\n", "<NEW_LINE>");
        # original_race_info = util.remove_space(original_race_info);

        #                  紫菊賞<NEW_LINE>/Pre-OP/京都<NEW_LINE>芝/2000m(中距離)/右
        match = re.search(r"(.+)<NEW_LINE>/(.+)/(.+)<NEW_LINE>(.+)/(.+)\((.+)\)/(.+)", original_race_info);
        if match:
            race_name = match.group(1);
            race_grade = match.group(2);
            racecourse = match.group(3);
            race_track = match.group(4);
            race_distance = match.group(5);
            race_distance_type = match.group(6);
            race_direction = match.group(7);
    
            race_info_obj["race_name"] = race_name;
            race_info_obj["race_grade"] = race_grade;
            race_info_obj["racecourse"] = racecourse;
            race_info_obj["race_track"] = race_track;
            race_info_obj["race_distance"] = race_distance;
            race_info_obj["race_distance_type"] = race_distance_type;
            race_info_obj["race_direction"] = race_direction;
        # print(f"race_name: {race_name}, race_grade: {race_grade}, racecourse: {racecourse}, race_track: {race_track}, race_distance: {race_distance}, race_distance_type: {race_distance_type}, race_direction: {race_direction}");


        race_data_jp.append(race_info_obj);
        util.write_json("../UmaData/race_data_jp.json", race_data_jp, 1);

        print(f"進度: {current_count}/{TOTAL_COUNT}");


dump_race_data_jp(is_dump_icon=True);