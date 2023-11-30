import json
import re
import utility


event_data_jp = utility.read_json_file(r"../UmaData/event_data_jp.json");
char_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_char.json");
card_convert_data = utility.read_json_file(r"../UmaData/event_data_jp_to_tw_card.json");


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
    "スキルPt": "技能點",
    "のヒント": "的靈感",
    "チーム＜シリウス＞": "＜天狼星＞隊",
    "になる": "", # "になる": "變成",
    "体力": "體力",
    "体力最大値": "最大體力值",
    "やる気アップ": "幹勁提升",
    "やる気が2段階アップ": "幹勁提升兩階",
    "やる気3段階ダウン": "幹勁下降三階",
    "の絆ゲージ": "的情誼量條",
    "ランダムで": "隨機地",
    "5種ステータスからランダムに2種を": "五種數值中隨機選兩種",
    "直前のトレーニングに応じたステータス": "當前選擇的訓練的數值",
    "シナリオに応じたNPC": "與劇本NPC相應",
    "アオハル": "青春",
}

choice_title_jp_to_tw_dict = {
    "選択肢なし": "無選項"
}


def convert_choice_effect_jp_to_tw(choice_effect):
    for jp, tw in choice_effect_jp_to_tw_dict.items():
        choice_effect = re.sub(jp, tw, choice_effect, flags=re.IGNORECASE)

    return choice_effect;

def convert_choice_title_jp_to_tw(choice_title):
    for jp, tw in choice_title_jp_to_tw_dict.items():
        choice_title = re.sub(jp, tw, choice_title, flags=re.IGNORECASE)

    return choice_title;

def convert_to_event_data_tw(convert_data):
    for owner_type, owner_type_v in event_data_jp.items():
        for rare, rare_v in owner_type_v.items():
            for jp_event_owner, jp_event_owner_v in rare_v.items():
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
                                    for key, value in choice_info.items():
                                        if (key == "choice_effect"):
                                            value = convert_choice_effect_jp_to_tw(value);
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