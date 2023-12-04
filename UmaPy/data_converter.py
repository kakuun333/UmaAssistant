import json
import re
import utility

# jp_data
event_data_jp = utility.read_json_file(r"../UmaData/event_data_jp.json");
skill_data_jp = utility.read_json_file(r"../UmaData/skill_data_jp.json");
scenario_event_data_jp = utility.read_json_file(r"../UmaData/scenario_event_data_jp.json");

# convert_data
char_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_char.json");
card_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_card.json");
skill_convert_data = utility.read_json_file(r"../UmaData/skill_data_jp_to_tw.json");
scenario_convert_data = utility.read_json_file(r"../UmaData/scenario_event_data_jp_to_tw.json");



event_data_tw = {
    "character": {
        "1_star": {},
        "2_star": {},
        "3_star": {},
    },
    "support_card": {
        "R": {},
        "SR": {},
        "SSR": {},
    },
};

skill_data_tw = {
    "blue": {
        "normal": {

        },
        "rare": {

        }
    },
    "green": {
        "normal": {

        },
        "rare": {
            
        }
    },
    "red": {
        "normal": {

        },
        "rare": {
            
        }
    },
    "yellow": {
        "normal": {

        },
        "rare": {
            
        }
    }
}

scenario_event_data_tw = {
    "URA": {
        
    },
    "aoharu": {
        
    },
    "meikura": {
        
    },
    "gurarai": {
        
    },
    "guramasu": {
        
    },
    "L'Arc": {

    },
};


choice_effect_jp_to_tw_dict = {
    # ステータス
    "スピード": "速度",
    "スタミナ": "持久力",
    "パワー": "力量",
    "根性": "意志力",
    "賢さ": "智力",

    # コンディション
    "夜ふかし気味": "睡眠不足",
    "太り気味": "體重過胖",
    "片頭痛": "偏頭痛",
    "なまけ癖": "懶惰成性",
    "肌あれ": "膚況不好",
    "切れ者": "天賦異稟",
    "注目株": "備受矚目",
    "大輪の輝き": "燦爛的光芒",
    "ファンとの約束・北海道": "與粉絲的約定・北海道",
    "ファンとの約束・北東": "與粉絲的約定・東北",
    "ファンとの約束・中山": "與粉絲的約定・中山",
    "ファンとの約束・関西": "與粉絲的約定・關西",
    "ファンとの約束・小倉": "與粉絲的約定・小倉",
    "情熱ゾーン：チーム＜シリウス＞": "熱情領域：＜天狼星＞隊",

    "愛嬌○": "討人喜歡○",
    "愛嬌◯": "討人喜歡◯",

    "練習上手○": "擅長練習○",
    "練習上手◯": "擅長練習◯",
    "練習上手◎": "擅長練習◎",

    "練習ベタ": "不擅長練習",
    "練習下手": "不擅長練習",

    "小さなほころび": "微小的裂痕",

    # その他
    "発生条件:駿川手綱と同じ練習後にランダムで発生": "發生條件:和駿川手綱一起練習後隨機發生",
    "以降、お出かけに誘えなくなる": "以後將無法再邀請出門",
    "桐生院トレーナーとお出かけ可能に": "可以與桐生院訓練師出門",
    "サポート効果により数値が変動": "數値會根據支援效果有所變動",
    "直前のトレーニングに応じたステータス": "當前選擇的訓練的數値",

    "シナリオに応じたNPC": "與劇本NPC相應",
    "シナリオNPC": "劇本NPC",

    "固有スキル": "固有技能",
    "ショップが開放される": "商店將開放",
    "スキルPt": "技能點",
    "のヒント": "的靈感",
    "チーム＜シリウス＞": "＜天狼星＞隊",
    "になる": "", # "になる": "變成",

    "体力": "體力",
    "体力最大値": "最大體力値",

    "やる気アップ": "幹勁提升",
    "やる気ダウン": "幹勁下降",

    "確率で": "有機率",

    "やる気2段階アップ": "幹勁提升兩階",
    "やる気が2段階アップ": "幹勁提升兩階",
    "やる気3段階ダウン": "幹勁下降三階",

    "の絆ゲージ": "的情誼量條",

    "マイナススキルを獲得": "獲得負面技能",

    "効果なし": "無效果",

    "ランダムで": "隨機",

    "1回目で上選択": "第一個事件選上面",
    "1回目で下選択で成功": "第一個事件選下面成功",
    "1回目で下選択で失敗": "第一個事件選下面失敗",

    "選択肢で連続イベント3が分岐する": "連續事件三會依照選擇而有所不同",


    "5種ステータスからランダムに1種を": "五種數値中隨機選一種",
    "5種ステータスからランダムに2種を": "五種數値中隨機選兩種",
    "5種ステータスからランダムに3種を": "五種數値中隨機選三種",
    "5種ステータスを": "五種數値",
    "5種ステータス": "五種數値",
    "1種ステータスを": "一種數値",
    "1種ステータス": "一種數値",

    "連続イベントが終了": "連續事件將結束",


    "アオハル": "青春",
    "もしくはヒント": "或者靈感",
}

choice_title_jp_to_tw_dict = {
    "選択肢なし": "無選項",

    "2回目で上選択": "連續事件二選上面",
    "2回目で下選択": "連續事件二選下面",

    "成功率高め": "成功率較高",
    "成功率低め": "成功率較低",

    ### 小栗帽（星光躍動） ###
    # 小栗帽是森林的導覽賽馬娘？
    "いつも助けられてるよ": "我一直都有受到你的幫助哦",
    "これからも頼りにしてる": "之後也要麻煩你幫忙了",
    # 被託付的意志
    "俺の想いも一緒だ！": "還有我的意志！",
    "みんなと一緒に勝とう！": "和大家一起獲勝吧！",


    # "": "",
    # "": "",


}


def convert_choice_effect_jp_to_tw(choice_effect, jp_event_owner = None, tw_event_owner = None):
    # 翻譯 jp 轉 tw
    for jp, tw in choice_effect_jp_to_tw_dict.items():
        if (jp == "スタミナ"):
            choice_effect = re.sub(rf'{jp}(?!キープ)', tw, choice_effect, flags=re.IGNORECASE);

        else:
            choice_effect = re.sub(jp, tw, choice_effect, flags=re.IGNORECASE);

    # 技能名稱 jp 轉 tw
    try:
        # <span class=\"skill_hint\">『弧線のプロフェッサー』</span>
        # "<span class=\"skill_hint\">『スプリントギア』</span>的靈感Lv<span class=\"status_plus_value\">+1</span>"
        jp_skill_title = re.match(r'<span class="skill_hint">『(.+)』</span>', choice_effect).group(1);
        print(jp_skill_title)
        try:
            tw_skill_title = skill_convert_data[jp_skill_title]["tw_skill_title"];
            
            choice_effect = re.sub(jp_skill_title, tw_skill_title, choice_effect);
        except:
            pass;
    except:
        pass;
    # 技能名稱 jp 轉 tw

    # 情誼量條的名稱 jp 轉 tw
    try:
        owner_name_pattern = r"(.+)（.+）";
        jp_event_owner = re.match(owner_name_pattern, jp_event_owner).group(1);
        tw_event_owner = re.match(owner_name_pattern, tw_event_owner).group(1);
        choice_effect = re.sub(jp_event_owner, tw_event_owner, choice_effect, flags=re.IGNORECASE);
    except:
        pass;
    # 情誼量條的名稱 jp 轉 tw



    return choice_effect;

def convert_choice_title_jp_to_tw(choice_title):
    for jp, tw in choice_title_jp_to_tw_dict.items():
        choice_title = re.sub(jp, tw, choice_title, flags=re.IGNORECASE)

    return choice_title;






##### skill_data_tw.json #####
def convert_to_skill_data_tw(convert_data):
    for color, color_v in skill_data_jp.items():
        for rare, rare_v in color_v.items():
            for jp_skill_title, jp_skill_title_v in rare_v.items():
                if jp_skill_title in convert_data:
                    skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]] = {};
                    for key, value in jp_skill_title_v.items():

                        if (key == "upper_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_upper_skill"];
                        elif (key == "lower_skill"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_lower_skill"];
                        elif (key == "skill_effect"):
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = convert_data[jp_skill_title]["tw_skill_effect"];
                        else:
                            skill_data_tw[color][rare][convert_data[jp_skill_title]["tw_skill_title"]][key] = value;

convert_to_skill_data_tw(skill_convert_data);

json_string = json.dumps(skill_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/skill_data_tw.json", json_string);

##### event_data_tw.json #####
def convert_to_event_data_tw(convert_data):
    for owner_type, owner_type_v in event_data_jp.items():
        for rare, rare_v in owner_type_v.items():
            for jp_event_owner, jp_event_owner_v in rare_v.items():
                # if jp_event_owner in convert_data:
                if jp_event_owner in convert_data:
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]] = {};
                    event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"] = [];

                    # print(card_convert_data[jp_event_owner]["tw_event_owner"]);
                    for event in jp_event_owner_v["event"]:
                        tw_event_obj = {};
                        for jp_event_title, jp_event_title_v in event.items():
                            if jp_event_title in convert_data[jp_event_owner]["event_title_dict"]:
                                tw_event_obj[convert_data[jp_event_owner]["event_title_dict"][jp_event_title]] = []
                                # event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"].append()
                                for choice_info in jp_event_title_v:
                                    tw_choice_obj = {};

                                    tw_event_owner = convert_data[jp_event_owner]["tw_event_owner"];

                                    for key, value in choice_info.items():
                                        if (key == "choice_effect"):
                                            value = convert_choice_effect_jp_to_tw(value, jp_event_owner, tw_event_owner);
                                        else:
                                            value = convert_choice_title_jp_to_tw(value);
                                        
                                        tw_choice_obj[key] = value;

                                    tw_event_obj[convert_data[jp_event_owner]["event_title_dict"][jp_event_title]].append(tw_choice_obj);
                            else:
                                continue;
                        if (tw_event_obj):
                            event_data_tw[owner_type][rare][convert_data[jp_event_owner]["tw_event_owner"]]["event"].append(tw_event_obj);

convert_to_event_data_tw(char_convert_data);
convert_to_event_data_tw(card_convert_data);

json_string = json.dumps(event_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/event_data_tw.json", json_string);

##### scenario_event_data_tw.json #####
def convert_to_scenario_event_data_tw(convert_data):
    for scenario_type, scenario_type_v in scenario_event_data_jp.items():
        for jp_event_title, jp_event_title_v in scenario_type_v.items():
            if jp_event_title in convert_data:
                scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]] = [];
                for choice in jp_event_title_v:
                    tw_choice_obj = {};

                    for key, value in choice.items():
                        if (key == "choice_effect"):
                            value = convert_choice_effect_jp_to_tw(value);
                        else:
                            value = convert_choice_title_jp_to_tw(value);

                        tw_choice_obj[key] = value;
                    scenario_event_data_tw[scenario_type][convert_data[jp_event_title]["tw_event_title"]].append(tw_choice_obj);

convert_to_scenario_event_data_tw(scenario_convert_data);

json_string = json.dumps(scenario_event_data_tw, indent=2, ensure_ascii=False);

utility.write_file("../UmaData/scenario_event_data_tw.json", json_string);