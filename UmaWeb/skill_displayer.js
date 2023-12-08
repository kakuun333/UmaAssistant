function createSkillHintContent() {
    let div = document.createElement("div");
    div.innerHTML = "TEST";
}


function updateSkillContent() {
    // var
    let hoveringSkill = false;
    let delayTimer;
    // var

    // element
    let skill_hint_content = document.getElementById("skill_hint_content");
    let skill_icon = document.getElementById("skill_icon");
    let skill_name = document.getElementById("skill_name");
    let skill_pt = document.getElementById("skill_pt");
    let skill_effect = document.getElementById("skill_effect");
    let upper_skill = document.getElementById("upper_skill");
    let lower_skill = document.getElementById("lower_skill");
    let upper_skill_title = document.getElementById("upper_skill_title");
    let lower_skill_title = document.getElementById("lower_skill_title");
    // element


    let skill_hint_elements = document.querySelectorAll(".skill_hint");
    for (let i = 0; i < skill_hint_elements.length; i++) {
        let skill_hint = skill_hint_elements[i];
        // 監聽滑鼠懸停
        skill_hint.addEventListener("mouseenter", function(event) {
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

            let content_width = rect.right - rect.left;
            let content_height = rect.bottom - rect.top;
            
            if (rect.left + content_width > windowWidth) {
                // console.log("超出視窗外！")
                // console.log("width: " + content_width, "height: " + content_height);
                // console.log("left: " + rect.left, "right: " + rect.right);
                let horizontal_offset = (rect.left + content_width) - windowWidth + 17;
                
                skill_hint_content.style.left = parseInt(skill_hint_content.style.left) - horizontal_offset + "px";
                skill_hint_content.style.right = parseInt(skill_hint_content.style.right) - horizontal_offset + "px";
            }
            if (rect.top + content_height > windowHeight) {
                // console.log("超出視窗外！")
                let vertical_offset = (rect.top + content_height) - windowHeight;

                skill_hint_content.style.top = parseInt(skill_hint_content.style.top) - vertical_offset + "px";
                skill_hint_content.style.bottom = parseInt(skill_hint_content.style.bottom) - vertical_offset + "px";
            }
            // style


            // skill json
            skill_data = null;

            if (GameServer == GameServerType.jp) {
                
                // 判斷日服文本語言
                if (JpServerLang == JpServerLangType.jp) {
                    skill_data = skill_data_jp;
                } else if (JpServerLang == JpServerLangType.tw) {
                    skill_data = skill_data_jp_trans_tw;
                }
                
            } else if (GameServer == GameServerType.tw) {
                skill_data = skill_data_tw;
            }

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
                                            } else if (skill_info == "skill_effect") {
                                                skill_effect.innerText = value;
                                            } else if (skill_info == "skill_icon_name") {
                                                skill_icon.src = "../UmaMisc/Image/Skill/"+ value +".png"
                                            } else if (skill_info == "upper_skill") {
                                                if (value != null) {
                                                    upper_skill_title.style.display = "inline";
                                                    upper_skill.style.display = "inline";
                                                    upper_skill.innerText = value;
                                                } else {
                                                    upper_skill_title.style.display = "none";
                                                    upper_skill.style.display = "none";
                                                }
                                            } else if (skill_info == "lower_skill") {
                                                if (value != null) {
                                                    lower_skill_title.style.display = "inline";
                                                    lower_skill.style.display = "inline";
                                                    lower_skill.innerText = value;
                                                } else {
                                                    lower_skill_title.style.display = "none";
                                                    lower_skill.style.display = "none";
                                                }
                                            }


                                            
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
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


updateSkillContent();