import util
import json
import re

from umaenum import *
from umaglobal import *

event_data_jp = util.read_json("../UmaData/new/event_data_jp.json");

def create_event_name_data_jp():

    def get_same_event_name_dict():
        same_event_name_dict = {};

        for event_type, event_type_v in event_data_jp.items():
            same_event_name_dict[event_type] = {};
            if event_type == EventDataType.SCENARIO:
                for scenario_type, scenario_type_v in event_type_v.items():
                    for event_name, event_name_v in scenario_type_v.items():
                        same_event_name_dict[event_type][event_name] = event_name;
            else:
                for rare, rare_v in event_type_v.items():
                    for event_owner, event_owner_v in rare_v.items():
                        for event_name, event_name_v in event_owner_v.items():
                            same_event_name_dict[event_type][event_name] = event_name;
    
        return same_event_name_dict;

    event_name_data = DEAULT_EVENT_NAME_DATA_DICT;

    same_event_name_dict = get_same_event_name_dict();

    print(same_event_name_dict);

    for event_type, event_type_v in same_event_name_dict.items():
        for event_name, event_name_v in event_type_v.items():
            event_name_data[event_type].append(event_name);
    # for event_type, event_type_v in event_data_jp.items():
    #     if event_type == EventDataType.SCENARIO:
    #         for scenario_type, scenario_type_v in event_type_v.items():
    #             for event_name, event_name_v in scenario_type_v.items():
    #                 if event_name == same_event_name_dict[event_type][event_name]:
    #                     event_name_data[event_type].append(event_name);
    #     else:
    #         for rare, rare_v in event_type_v.items():
    #             for event_owner, event_owner_v in rare_v.items():
    #                 for event_name, event_name_v in event_owner_v.items():
    #                     if event_name == same_event_name_dict[event_type][event_name]:
    #                         event_name_data[event_type].append(event_name);

    util.write_json("../UmaData/new/event_name_data_jp.json", event_name_data);

create_event_name_data_jp();

