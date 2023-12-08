import re
import time
import json
import utility
from selenium import webdriver
from selenium.webdriver.common.by import By


driver = webdriver.Chrome();

scenario_event_tw_dict = {

};



driver.get("https://wiki.biligame.com/umamusume/%E7%B9%81%E4%B8%AD%E5%B7%85%E5%B3%B0%E6%9D%AF%E4%BA%8B%E4%BB%B6%E4%B8%80%E8%A7%88");

div_list = driver.find_elements(By.CLASS_NAME, "sj-an");


for div in div_list:
    a = div.find_element(By.XPATH, ".//a");
    
    jp_event_title = re.match(".+/(.+)", a.get_attribute("title")).group(1);
    tw_event_title = a.text;

    scenario_event_tw_dict[jp_event_title] = {
        "tw_event_title": tw_event_title,
    };


json_string = json.dumps(scenario_event_tw_dict, indent=2, ensure_ascii=False);
utility.write_file("../UmaData/scenario_event_data_jp_cvt_tw.json", json_string);