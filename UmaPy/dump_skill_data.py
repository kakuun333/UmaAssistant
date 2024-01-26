import re
import time
import json
import util

from umaenum import *
from umaglobal import *

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options


chrome_options = Options()
chrome_options.add_argument("--new-tab")  

driver = webdriver.Chrome(options=chrome_options)

skill_data_jp = util.read_json("../UmaData/event_data_jp.json") or DEFAULT_SKILL_DATA_DICT;



def dump_skill_data_jp():
    driver.get(DataUrl.JP_ALL_SKILL_LIST);

    driver.implicitly_wait(3);

    

    normal_label = driver.find_element(By.XPATH, "//label[@for='FilterCB0_3' and text()='ノーマル']")
    rare_label = driver.find_element(By.XPATH, "//label[@for='FilterCB0_2' and text()='レア']")
    util.click(driver, normal_label)
    util.click(driver, rare_label)

    driver.implicitly_wait(1);


    # rare_skill_list = driver.find_elements(By.CLASS_NAME, "is-rare");

    # for rare_skill in rare_skill_list:
    #     skill_url = rare_skill.find_element(By.TAG_NAME, "a").get_attribute("href");
    #     util.open_url(driver, skill_url);
    #     time.sleep(2);


    normal_skill_list = driver.find_elements(By.XPATH, "//li[contains(@filters, 'normal')]")
    for normal_skill in normal_skill_list:
        # _inner-table
        result = driver.execute_cdp_cmd('Runtime.evaluate', {'expression': 'document.querySelector("._inner-table")'})
        objectId = result["result"]["objectId"];


        # properties = driver.execute_cdp_cmd('Runtime.getProperties', {'objectId': '{}'.format(objectId)})

        event_listeners = driver.execute_cdp_cmd('DOMDebugger.getEventListeners', {'objectId': result["result"]["objectId"], 'depth': -1})

        touchstart_listener = next((listener for listener in event_listeners['listeners'] if listener['type'] == 'touchstart'), None)
        print(touchstart_listener);

        if touchstart_listener:
            # 获取事件监听器的 handler 对象
            handler_object = touchstart_listener.get('handler', {})
            print("handler_object:", handler_object);

            # if handler_object_id:
            #     # 使用 Runtime.getProperties 获取 handler 对象的属性
            #     properties_result = driver.execute_cdp_cmd('Runtime.getProperties', {'objectId': handler_object_id})
            #     print("properties_result:", properties_result);

            #     # 找到 [[Scopes]] 对象
            #     scopes_object = next((prop for prop in properties_result.get('result', []) if prop.get('name') == '[[Scopes]]'), None)

            #     print("scopes_object:", scopes_object);
            #     if scopes_object:
            #         # 获取 [[Scopes]] 中的 [1] 中的 URL 属性
            #         url_property = next((prop for prop in scopes_object.get('value', {}).get('objectId', {}).get('result', []) if prop.get('name') == '1'), None)

            #         if url_property:
            #             url = url_property.get('value', {}).get('value')
            #             print(url)



        print("已執行！")
        time.sleep(20);




dump_skill_data_jp();