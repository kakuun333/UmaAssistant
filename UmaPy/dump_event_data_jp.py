import re
import time
import util

from umaenum import *
from umaglobal import *

from selenium import webdriver
from selenium.webdriver.common.by import By




driver = webdriver.Chrome();






skill_data_jp = util.read_json("../UmaData/skill_data_jp.json");
event_data_jp = util.read_json("../UmaData/event_data_jp.json") or DEAULT_EVENT_DATA_DICT;
process_choice_effect_data = util.read_json("../UmaData/convert_data/process_choice_effect_data.json");

########## functions ##########



def dump_event(event_data_type, rare, event_owner):
    ### 獲取 event ###

    h2 = driver.find_element(By.XPATH, "//h2[contains(text(), '発生イベントと選択肢一覧')]");
    print(f"h2.text: {h2.text}");
    
    h4_list = h2.find_elements(By.XPATH, "following-sibling::h4");


    for h4 in h4_list:

        ### event_name ###
        print("h4.text", h4.text);
        event_name = h4.text;
        if (event_data_type == EventDataType.CHARACTER):
            if event_name == "With": continue; # 不要獲取 With 事件，With 事件統一到 larc 主要劇情事件
        
            if event_name == "レース勝利！(1着)": event_name = "レース勝利！";
            if event_name == "レース入着(2~5着)": event_name = "レース入着";
            if event_name == "レース敗北(6着以下)": event_name = "レース敗北";

        
        event_name = util.sub(event_name, r"\(", "（");
        event_name = util.sub(event_name, r"\)", "）");
        event_name = util.sub(event_name, "〜", "～");
        event_name = util.sub(event_name, "　", "");
        event_name = util.sub(event_name, ":", "：");
        

        ### choice ###
        choice_list = [];
        try:
            uma_choice_table = h4.find_element(By.XPATH, "following-sibling::div[@class='uma_choice_table']");
        except:
            print(f"uma_choice_table 發生例外！ h4.text: {h4.text}"); # driver.get("https://gamewith.jp/uma-musume/article/show/392647");
            break;
        
        tr_list = uma_choice_table.find_elements(By.XPATH, ".//tr");
        for tr in tr_list:
            if not tr.text: continue;
            ### choice_name ###
            th = tr.find_element(By.XPATH, ".//th");
            choice_name = th.text;
            # print(choice_name);

            ### choice_effect ###
            th = tr.find_element(By.XPATH, ".//td");
            choice_effect = th.text;

            # 跳過沒有效果的事件
            if (choice_effect == "効果なし"): continue;

            choice_effect = util.process_choice_effect(choice_effect, process_choice_effect_data, skill_data_jp);
            # print(choice_effect);

            choice_obj = {
                "choice_name": choice_name,
                "choice_effect": choice_effect
            };
            choice_list.append(choice_obj);

        event_data_jp[event_data_type][rare][event_owner][event_name] = choice_list;


def dump_larc_event():
    # 隨便拿一個角色獲取 With 事件
    driver.get("https://gamewith.jp/uma-musume/article/show/257412");
    util.switch_tab(driver, util.Tab.NEWEST);

    h4 = driver.find_element(By.XPATH, "//h4[text()='With']");
    event_name = h4.text;

    ### choice ###
    choice_list = [];

    uma_choice_table = h4.find_element(By.XPATH, "following-sibling::div[@class='uma_choice_table']");
    
    tr_list = uma_choice_table.find_elements(By.XPATH, ".//tr");
    for tr in tr_list:
        if not tr.text: continue;
        ### choice_name ###
        th = tr.find_element(By.XPATH, ".//th");
        choice_name = th.text;
        # print(choice_name);

        ### choice_effect ###
        th = tr.find_element(By.XPATH, ".//td");
        choice_effect = th.text;

        choice_effect = util.process_choice_effect(choice_effect, process_choice_effect_data, skill_data_jp);
        # print(choice_effect);

        choice_obj = {
            "choice_name": choice_name,
            "choice_effect": choice_effect
        };
        choice_list.append(choice_obj);

    event_data_jp[EventDataType.SCENARIO][ScenarioType.LARC][event_name] = choice_list;

# def dump_guramasu_event():
#     driver.get("https://gamewith.jp/uma-musume/article/show/389470");
#     util.switch_tab(driver, util.Tab.NEWEST);

#     time.sleep(3);

#     # uma_megami_eiti
#     uma_megami_eiti = driver.find_element(By.CLASS_NAME, "uma_megami_eiti");
#     tr_list = uma_megami_eiti.find_elements(By.XPATH, ".//tr");
#     for idx, tr in enumerate(tr_list):
#         if idx == 0 or idx == 4 or idx == 8:
#             choice_name = tr.text;
#         else:


########## 倒出支援卡事件資料 ##########
def dump_sapoka_event_data_jp(single_dump_mode: bool = False, url: str = ""):

    def dump_event_data():
        
        # driver.implicitly_wait(0.5);
        
        ### owner ###
        # 【ウマ娘】ホッコータルマエ(SSRサポート)
        _title_div = driver.find_element(By.TAG_NAME, "h1");
        match_obj = re.match(r"【ウマ娘】(.+)\(.+\)", _title_div.text);
        owner = match_obj.group(1);
        
        ### rare, another_name ###
        rare = None;
        another_name = None;
        th_list = driver.find_elements(By.TAG_NAME, "th");
        
        for th in th_list:
            if th.text == "レア" and th.get_attribute("width") == "30%":
                td = th.find_element(By.XPATH, "following-sibling::td");
                
                a = td.find_element(By.XPATH, ".//a");
                rare = a.text.lower();
            elif th.text == "二つ名":
                td = th.find_element(By.XPATH, "following-sibling::td");
                another_name = td.text;
        
        ### event_owner ###
        event_owner = f"{owner}（{another_name}）";

        print(event_owner);

        event_data_jp["sapoka"][rare][event_owner] = {};
        
        ### 獲取 event ###
        dump_event(EventDataType.SAPOKA, rare, event_owner);

    #############################################################
    if (single_dump_mode):
        driver.get(url);
        time.sleep(6);
        dump_event_data();
        # 寫入 json
        util.write_json("../UmaData/event_data_jp.json", event_data_jp);
        print("dump_character_event_data_jp(): single_dump_mode 執行完畢！");
    else:
        driver.get(DataUrl.JP_ALL_SAPOKA_LIST);

        time.sleep(6);

        # 獲取支援卡事件
        sort_table = driver.find_element(By.CLASS_NAME, "sorttable");
        tbody = sort_table.find_element(By.TAG_NAME, "tbody");
        tr_list = tbody.find_elements(By.TAG_NAME, "tr");

        MAX_PROCRESS = len(tr_list);
        current_procress = 0;

        for tr in tr_list:
            current_procress += 1;
            if tr.get_attribute("class") == "":
                print(f"進度: {int((current_procress / MAX_PROCRESS) * 100)}% [{current_procress} / {MAX_PROCRESS}]")
                continue;

            # 尋找網址並在新分頁開啟
            card_url = tr.find_element(By.XPATH, ".//a").get_attribute("href");
            util.open_url(driver, card_url);
            util.switch_tab(driver, util.Tab.NEWEST);

            # 獲取 event_data
            dump_event_data();

            # 寫入 json
            util.write_json("../UmaData/event_data_jp.json", event_data_jp);

            driver.close();

            util.switch_tab(driver, util.Tab.FIRST);

            print(f"進度: {int((current_procress / MAX_PROCRESS) * 100)}% [{current_procress} / {MAX_PROCRESS}]")


########## 倒出角色事件資料 ##########
def dump_character_event_data_jp(single_dump_mode: bool = False, url: str = ""):
    
    def dump_event_data():

        ##### owner #####
        # 【ウマ娘】ヴィブロス(星3)の評価とイベント
        _title_div = driver.find_element(By.TAG_NAME, "h1");
        match_obj = re.match(r"【ウマ娘】(.+)\(.+\)", _title_div.text);
        owner = match_obj.group(1);

        # 去掉 水着
        owner = util.sub(owner, "水着", ""); 
    
        ##### rare, another_name #####
        rare = None;
        another_name = None;

        th_list = driver.find_elements(By.TAG_NAME, "th");
        for th in th_list:
            if th.text == "初期レア":
                td = th.find_element(By.XPATH, "following-sibling::td");
                a = td.find_element(By.XPATH, ".//a");
                rare = a.text;
                if rare == "星3": rare = "3_star";
                elif rare == "星2": rare = "2_star";
                elif rare == "星1": rare = "1_star";
            elif th.text == "名称":
                td = th.find_element(By.XPATH, "following-sibling::td");
                another_name = td.text;
    
        ##### event_owner #####
        event_owner = f"{owner}（{another_name}）";

        print(event_owner);
    
        event_data_jp["character"][rare][event_owner] = {};
    
        ### 獲取 event ###
        dump_event(EventDataType.CHARACTER, rare, event_owner);

    #############################################################
    if (single_dump_mode):
        driver.get(url);
        time.sleep(6);
        dump_event_data();
        # 寫入 json
        util.write_json("../UmaData/event_data_jp.json", event_data_jp);
        print("dump_character_event_data_jp(): single_dump_mode 執行完畢！");
    else:
        driver.get(DataUrl.JP_ALL_CHARACTER_LIST);

        time.sleep(6);

        umamusume_ikusei_ichiran = driver.find_element(By.CLASS_NAME, "umamusume-ikusei-ichiran");
        tbody = umamusume_ikusei_ichiran.find_element(By.TAG_NAME, "tbody");
        tr_list = tbody.find_elements(By.TAG_NAME, "tr");

        MAX_PROCRESS = len(tr_list);
        current_procress = 0;

        for tr in tr_list:
            current_procress += 1;
            # if current_procress < skip_count: continue;

            char_url = tr.find_element(By.XPATH, ".//a").get_attribute("href");

            util.open_url(driver, char_url);
            util.switch_tab(driver, util.Tab.NEWEST);

            # 獲取 event_data
            dump_event_data();

            # 寫入 json
            util.write_json("../UmaData/event_data_jp.json", event_data_jp);

            driver.close();

            util.switch_tab(driver, util.Tab.FIRST);

            print(f"進度: {int((current_procress / MAX_PROCRESS) * 100)}% [{current_procress} / {MAX_PROCRESS}]")


########## 倒出劇本事件資料 ##########
def get_scenario_event_data_jp(scenario_type):
    event_name_list = [];  #161
    choice_list = [];       #161
    h3_list = driver.find_elements(By.TAG_NAME, "h3");
    div_choice_list = driver.find_elements(By.CLASS_NAME, "uma_choice_table");
    
    for h3 in h3_list:
        event_name = h3.text;
        
        event_name_list.append(event_name);
        
    for choice_element in div_choice_list:
        tr_list = choice_element.find_elements(By.TAG_NAME, "tr");

        choice = [];

        for tr in tr_list:
            choice_name_element = tr.find_element(By.XPATH, ".//th");
            choice_name = choice_name_element.text;
            choice_effect_element = tr.find_element(By.XPATH, ".//td");
            choice_effect = choice_effect_element.text;

            # 跳過沒有效果的事件
            if (choice_effect == "効果なし"): continue;

            choice_effect = util.process_choice_effect(choice_effect, process_choice_effect_data, skill_data_jp);

            # 替換 ScenarioStatus
            # グラライ ScenarioStatus
            choice_effect = re.sub(r'ダンス', rf'<img src="../UmaMisc/Image/Scenario/performance_Da.png">ダンス', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'ボーカル', rf'<img src="../UmaMisc/Image/Scenario/performance_Vo.png">ボーカル', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'パッション', rf'<img src="../UmaMisc/Image/Scenario/performance_Pa.png">パッション', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'ビジュアル', rf'<img src="../UmaMisc/Image/Scenario/performance_Vi.png">ビジュアル', choice_effect, flags=re.IGNORECASE);
            choice_effect = re.sub(r'メンタル', rf'<img src="../UmaMisc/Image/Scenario/performance_Me.png">メンタル', choice_effect, flags=re.IGNORECASE);

            choice_info = {
                "choice_name": choice_name,
                "choice_effect": choice_effect,
            }

            choice.append(choice_info);

        choice_list.append(choice);

    for event_name, choice in zip(event_name_list, choice_list):
        # 如果沒有事件效果就不放入字典裡面
        if not choice: continue;

        event_data_jp[EventDataType.SCENARIO][scenario_type][event_name] = choice;


def dump_scenario_event_data_jp():
    # アオハル
    driver.get("https://gamewith.jp/uma-musume/article/show/292841");
    util.switch_tab(driver, util.Tab.NEWEST);
    get_scenario_event_data_jp(ScenarioType.AOHARU);
    util.write_json("../UmaData/event_data_jp.json", event_data_jp);
    # メイクラ
    driver.get("https://gamewith.jp/uma-musume/article/show/320396");
    util.switch_tab(driver, util.Tab.NEWEST);
    get_scenario_event_data_jp(ScenarioType.MEIKURA);
    util.write_json("../UmaData/event_data_jp.json", event_data_jp);
    # グラライ 
    driver.get("https://gamewith.jp/uma-musume/article/show/360338");
    util.switch_tab(driver, util.Tab.NEWEST);
    get_scenario_event_data_jp(ScenarioType.GURARAI);
    util.write_json("../UmaData/event_data_jp.json", event_data_jp);
    # グラマス
    # https://gamewith.jp/uma-musume/article/show/389470
    # dump_guramasu_event();
    
    # L'Arc
    dump_larc_event();
    util.write_json("../UmaData/event_data_jp.json", event_data_jp);






############################################################

# dump_character_event_data_jp();
# dump_sapoka_event_data_jp();
# dump_scenario_event_data_jp();


##### single_dump_mode #####


dump_character_event_data_jp(single_dump_mode=True, url="https://gamewith.jp/uma-musume/article/show/401064");
dump_character_event_data_jp(single_dump_mode=True, url="https://gamewith.jp/uma-musume/article/show/327361");



# dump_sapoka_event_data_jp(single_dump_mode=True, url="https://gamewith.jp/uma-musume/article/show/359859");
# dump_sapoka_event_data_jp(single_dump_mode=True, url="https://gamewith.jp/uma-musume/article/show/360184");
