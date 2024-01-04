// function createSkillHintContent() {
//     let div = document.createElement("div");
//     div.innerHTML = "TEST";
// }


function getSize(element) {
    let rect = element.getBoundingClientRect();
    let width = rect.right - rect.left;
    let height = rect.bottom - rect.top;

    const tmp = {
        width: width,
        height: height
    }

    return tmp;
}

function cleanSkillLabelRow() {
    const skill_effect = document.getElementById("skill_effect");
    const skill_condition = document.getElementById("skill_condition");

    // const children = skill_effect_table.children;

    // for (var i = 0; i < children.length; i++) {
    //     console.log(children[i])
    //     if (children[i].firstChild.className != "table_row_title") {
    //         children[i].remove();
    //     }
    // }

    while (skill_effect.lastChild) {
        skill_effect.removeChild(skill_effect.lastChild);
    }

    while (skill_condition.lastChild) {
        skill_condition.removeChild(skill_condition.lastChild);
    }
}

function createSkillLabel(skillDataType, skill_effect_title, skill_effect_data) {
    let skill_label = null;

    let targetClassName = null;

    switch (skillDataType) {
        case "skill_effect":
            skill_label = document.getElementById("skill_effect");
            targetClassName = "skill_effect_data";
            break;
        case "skill_condition":
            skill_label = document.getElementById("skill_condition");
            targetClassName = "skill_condition_data";
            break;
    }


    // ------------------------------------- //
    const tr = document.createElement("tr");
    skill_label.appendChild(tr);

    // ------------------------------------- //
    const th = document.createElement("th");
    th.className = "enhance_skill_data " + targetClassName;
    
    th.innerHTML = "<span>" + skill_effect_title + "</span>";
    tr.appendChild(th);
    
    // ------------------------------------- //
    const td = document.createElement("td");
    td.innerHTML = "<span>" + skill_effect_data + "</span>";
    tr.appendChild(td);
}

function updateSkillContent() {
    // var
    let hoveringSkill = false;
    let delayTimer;
    // var

    // element
    const skill_hint_content = document.getElementById("skill_hint_content");
    const skill_icon = document.getElementById("skill_icon");
    const skill_name = document.getElementById("skill_name");
    const skill_pt = document.getElementById("skill_pt");
    const skill_description = document.getElementById("skill_description");
    const upper_skill = document.getElementById("upper_skill");
    const lower_skill = document.getElementById("lower_skill");
    const upper_skill_title = document.getElementById("upper_skill_title");
    const lower_skill_title = document.getElementById("lower_skill_title");
    const skill_table = document.getElementById("skill_table");
    const skill_effect_table = document.getElementById("skill_effect_table");
    // element


    let skill_hint_elements = document.querySelectorAll(".skill_hint");
    for (let i = 0; i < skill_hint_elements.length; i++) {
        let skill_hint = skill_hint_elements[i];
        // 監聽滑鼠懸停
        skill_hint.addEventListener("mouseenter", function(event) {
            // skill json
            skill_data = null;

            switch (GameServer)
            {
            case GameServerType.jp:
                switch (JpServerLang)
                {
                case JpServerLangType.jp:
                    skill_data = skill_data_jp;
                    break;
                case JpServerLangType.tw:
                    skill_data = skill_data_jp_trans_tw;
                    break;
                }
                break;

            case GameServerType.tw:
                skill_data = skill_data_tw;
                break;
            }
            // if (GameServer == GameServerType.jp) {
                
            //     // 判斷日服文本語言
            //     if (JpServerLang == JpServerLangType.jp) {
            //         skill_data = skill_data_jp;
            //     } else if (JpServerLang == JpServerLangType.tw) {
            //         skill_data = skill_data_jp_trans_tw;
            //     }
                
            // } else if (GameServer == GameServerType.tw) {
            //     skill_data = skill_data_tw;
            // }

            for (let color in skill_data) {
                if (skill_data.hasOwnProperty(color)) {
                    let color_obj = skill_data[color];
                    for (let skill_rare in color_obj) {
                        if (color_obj.hasOwnProperty(skill_rare)) {
                            let rare_obj = color_obj[skill_rare];
                            for (let json_skill_name in rare_obj) {
                                if (rare_obj.hasOwnProperty(json_skill_name)) {
                                    let skill_name_obj = rare_obj[json_skill_name];
                                    
                                    // <span class=\"skill_hint\">『負けん気』
                                    let pattern = new RegExp("<span class=\"skill_hint\">『(.+)』");
                                    // 測試字符串是否匹配正規表達式
                                    let match_name = skill_hint.outerHTML.match(pattern);

                                    if (json_skill_name == match_name[1]) {

                                        skill_name.innerText = json_skill_name;

                                        if (skill_rare == "rare") {
                                            skill_hint_content.style.background = 'linear-gradient(to right,  rgb(254, 242, 176), rgb(254, 195, 57))';
                                        } else if (skill_rare == "normal") {
                                            skill_hint_content.style.background = 'linear-gradient(to right,  rgb(248, 248, 248), rgb(199, 199, 212))';
                                        }

                                        for (let skill_info in skill_name_obj) {
                                            let value = skill_name_obj[skill_info];

                                            if (skill_info == "skill_pt") {
                                                skill_pt.innerText = value;
                                            } else if (skill_info == "skill_description") {
                                                skill_description.innerText = value;
                                            } else if (skill_info == "skill_icon_name") {
                                                skill_icon.src = "../UmaMisc/Image/Skill/" + value + ".png"
                                            } else if (skill_info == "upper_skill") {
                                                if (value != null) {
                                                    upper_skill_title.parentElement.parentElement.style.display = "table-row";
                                                    // upper_skill_title.style.display = "inline";
                                                    // upper_skill.style.display = "inline";
                                                    upper_skill.innerText = value;
                                                } else {
                                                    upper_skill_title.parentElement.parentElement.style.display = "none";
                                                }
                                            } else if (skill_info == "lower_skill") {
                                                if (value != null) {
                                                    lower_skill_title.parentElement.parentElement.style.display = "table-row";
                                                    // lower_skill_title.style.display = "inline";
                                                    // lower_skill.style.display = "inline";
                                                    lower_skill.innerText = value;
                                                } else {
                                                    lower_skill_title.parentElement.parentElement.style.display = "none";
                                                }
                                            }
                                        }


                                        let enhance_skill_data = null;

                                        switch (GameServer)
                                        {
                                        case GameServerType.jp:
                                            switch (JpServerLang)
                                            {
                                            case JpServerLangType.jp:
                                                enhance_skill_data = enhance_skill_data_jp;
                                                break;
                                            case JpServerLangType.tw:
                                                enhance_skill_data = enhance_skill_data_jp;
                                                break;
                                            }
                                            break;
                            
                                        case GameServerType.tw:
                                            enhance_skill_data = enhance_skill_data_tw;
                                            break;
                                        }

                                        cleanSkillLabelRow();

                                        // 添加進階技能詳細資訊
                                        for (let skill_data_type in enhance_skill_data[json_skill_name]) {
                                            const skill_data_v = enhance_skill_data[json_skill_name][skill_data_type];

                                            for (let skill_data_title in skill_data_v) {
                                                const skill_data_data = skill_data_v[skill_data_title];
                                                // console.log(skill_data_title, skill_data_data);

                                                if (skill_data_data == null) continue;

                                                createSkillLabel(skill_data_type, skill_data_title, skill_data_data);
                                            }
                                        }

                                        enhance_data_list = document.querySelectorAll(".enhance_data");

                                        for (let i = 0; i < enhance_data_list.length; ++i) {
                                            if (skill_rare == "normal") {
                                                enhance_data_list[i].style.background = "linear-gradient(to right,  rgb(255, 255, 255), rgb(214, 214, 233), rgb(248, 248, 248), rgb(248, 248, 248))";
                                            } else if (skill_rare == "rare") {
                                                enhance_data_list[i].style.background = "linear-gradient(to right,  rgb(255, 250, 156), rgb(254, 210, 137), rgb(255, 240, 156), rgb(255, 240, 156))";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // enhance_data_list = document.querySelectorAll(".enhance_data");
            // for (let i = 0; i < enhance_data_list.length; ++i) {
            //     if (show_enhance_skill) {
            //         enhance_data_list[i].style.display = "table_row";
            //     } else {
            //         enhance_data_list[i].style.display = "none";
            //     }
            // }
            


            // style
            let mouseX = event.clientX;
            let mouseY = event.clientY;

            skill_hint_content.style.top = mouseY + 'px';
            skill_hint_content.style.bottom = '0px';
            skill_hint_content.style.left = mouseX + 'px';
            skill_hint_content.style.right = '0px';

            skill_hint_content.style.display = "inline";

            let windowWidth = window.innerWidth;
            let windowHeight = window.innerHeight;
            let rect = skill_hint_content.getBoundingClientRect();

            // console.log("windowWidth: " + windowWidth, "windowHeight: " + windowHeight);
            // console.log("top: " + rect.top, "bottom: " + rect.bottom, "left: " + rect.left, "right: " + rect.right);

            // let content_width = rect.right - rect.left;
            // let content_height = rect.bottom - rect.top;

            const skill_table_size = getSize(skill_table);

            
            if (rect.left + skill_table_size.width > windowWidth) {
                // console.log("超出視窗外！")
                // console.log("width: " + content_width, "height: " + content_height);
                // console.log("left: " + rect.left, "right: " + rect.right);
                let horizontal_offset = (rect.left + skill_table_size.width) - windowWidth + 17;
                
                skill_hint_content.style.left = parseInt(skill_hint_content.style.left) - horizontal_offset + "px";
                skill_hint_content.style.right = parseInt(skill_hint_content.style.right) - horizontal_offset + "px";
            }
            if (rect.top + skill_table_size.height > windowHeight) {
                // console.log("超出視窗外！")

                let vertical_offset = (rect.top + skill_table_size.height) - windowHeight;

                
                skill_hint_content.style.top = parseInt(skill_hint_content.style.top) - vertical_offset + "px";
                skill_hint_content.style.bottom = parseInt(skill_hint_content.style.bottom) - vertical_offset + "px";
            }

            console.log(skill_table_size.width, skill_table_size.height);

            // skill_hint_content.style.width = parseInt(skill_table_size.width) + "px";
            skill_hint_content.style.height = parseInt(skill_table_size.height) + "px";
            // style
        });

        // 監聽滑鼠離開
        skill_hint.addEventListener("mouseleave", function(event) {
            skill_hint_content.style.display = "none";
        });
    }

}



function readJson(jsonPath, callback) {
    const READY_STATE_DONE = 4; // 資料接收完畢
    const STATUS_SUCCESS = 200; // 請求成功

    let xhr = new XMLHttpRequest();

    xhr.onreadystatechange = function() {
        if (xhr.readyState === READY_STATE_DONE) {
            if (xhr.status === STATUS_SUCCESS) {
                // 解析 JSON
                let jsonData = JSON.parse(xhr.responseText);
                callback(jsonData);
            } else {
                console.error('Error:', xhr.statusText);
            }
        }
    };
    
    xhr.open('GET', jsonPath, true);
    xhr.send();
}

function hiddenSkillHintContent() {
    let content = document.getElementById("skill_hint_content");

    content.style.display = "none";
}

function changeSkillGameServer(gameServer) {
    GameServer = gameServer;
}

function changeJpServerLang(language) {
    JpServerLang = language;
}

const GameServerType = {
    jp: 0,
    tw: 1,
};
const JpServerLangType = {
    jp: 0,
    tw: 1,
}

let skill_data_jp = null;
let skill_data_tw = null;
let skill_data_jp_trans_tw = null;
let enhance_skill_data_jp = null;
let enhance_skill_data_tw = null;


let GameServer = GameServerType.jp;
let JpServerLang = JpServerLangType.jp;

readJson("../UmaData/skill_data_jp.json", function(jsonData){
    skill_data_jp = jsonData;
});

readJson("../UmaData/skill_data_tw.json", function(jsonData){
    skill_data_tw = jsonData;
});

readJson("../UmaData/skill_data_jp_trans_tw.json", function(jsonData){
    skill_data_jp_trans_tw = jsonData;
});

readJson("../UmaData/enhance_skill_data_jp.json", function(jsonData){
    enhance_skill_data_jp = jsonData;
});

readJson("../UmaData/enhance_skill_data_tw.json", function(jsonData){
    enhance_skill_data_tw = jsonData;
});


updateSkillContent();