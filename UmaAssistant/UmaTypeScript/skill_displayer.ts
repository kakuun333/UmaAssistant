function cleanSkillLabelRow(): void
{
    const skill_effect = document.getElementById("skill_effect")!;
    const skill_condition = document.getElementById("skill_condition")!;

    while (skill_effect.lastChild)
    {
        skill_effect.removeChild(skill_effect.lastChild);
    }

    while (skill_condition.lastChild)
    {
        skill_condition.removeChild(skill_condition.lastChild);
    }
}

function createSkillLabel(skillDataType: SkillDataType, skill_effect_title: string, skill_effect_data: string): void
{
    let skill_label: Element | null = null;

    let targetClassName: string | null = null;

    switch (skillDataType)
    {
        case SkillDataType.SKILL_EFFECT:
            skill_label = document.getElementById("skill_effect");
            targetClassName = "skill_effect_data";
            break;
        case SkillDataType.SKILL_CONDITION:
            skill_label = document.getElementById("skill_condition");
            targetClassName = "skill_condition_data";
            break;
    }


    // ------------------------------------- //
    const tr = document.createElement("tr");
    skill_label!.appendChild(tr);

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

function findSkillData(event: any, skill_hint: Element): void
{
    // element
    const skill_hint_content = document.getElementById("skill_hint_content")!;
    const skill_icon = document.getElementById("skill_icon")! as HTMLImageElement;
    const skill_name = document.getElementById("skill_name")!;
    const skill_pt = document.getElementById("skill_pt")!;
    const skill_description = document.getElementById("skill_description")!;
    const upper_skill = document.getElementById("upper_skill")!;
    const lower_skill = document.getElementById("lower_skill")!;
    const upper_skill_title = document.getElementById("upper_skill_title")!;
    const lower_skill_title = document.getElementById("lower_skill_title")!;
    const skill_table = document.getElementById("skill_table")!;
    // element

    const skill_hint_pattern = new RegExp("<span class=\"skill_hint\"(.+)?>『(.+)』");


    // skill json
    let skill_data = null;

    switch (Config.GameServer)
    {
    case GameServer.JP:
        switch (Config.JpServerLanguage)
        {
        case JpServerLanguage.JP:
            skill_data = skill_data_jp;
            break;
        case JpServerLanguage.TW:
            skill_data = skill_data_jp_trans_tw;
            break;
        }
        break;
    case GameServer.TW:
        skill_data = skill_data_tw;
        break;
    }

    for (let color in skill_data) {
        // if (!skill_data.hasOwnProperty(color)) continue;
        let color_obj = skill_data[color];
        for (let skill_rare in color_obj) {
            // if (!color_obj.hasOwnProperty(skill_rare)) continue;
            let rare_obj = color_obj[skill_rare];
            for (let json_skill_name in rare_obj) {
                // if (!rare_obj.hasOwnProperty(json_skill_name)) continue;
                let skill_name_obj = rare_obj[json_skill_name];
                // <span class=\"skill_hint\">『負けん気』
                let match_skill_name = skill_hint.outerHTML.match(skill_hint_pattern)!;
                // 第二個括號捕獲的字串: match_skill_name[2]
                if (json_skill_name == match_skill_name[2]) {

                    skill_name.innerText = json_skill_name;

                    // 更新背景顏色
                    if (skill_rare == "rare") {
                        skill_hint_content.style.background = 'linear-gradient(to right,  rgb(254, 242, 176), rgb(254, 195, 57))';
                    } else if (skill_rare == "normal") {
                        skill_hint_content.style.background = 'linear-gradient(to right,  rgb(248, 248, 248), rgb(199, 199, 212))';
                    }

                    // ===== 更新基本的 skill 資訊 ===== //
                    // skill_pt
                    if (skill_name_obj["skill_pt"] != undefined) {
                        skill_pt.innerText = skill_name_obj["skill_pt"];
                    } else {
                        skill_pt.parentElement!.parentElement!.style.display = "none";
                    }
                    // skill_description
                    if (skill_name_obj["skill_description"] != undefined) {
                        skill_description.innerText = skill_name_obj["skill_description"];
                    }
                    // skill_icon_name
                    if (skill_name_obj["skill_icon_name"] != undefined) {
                        skill_icon.src = "../UmaMisc/Image/Skill/" + skill_name_obj["skill_icon_name"] + ".png"
                    }
                    // upper_skill
                    if (skill_name_obj["upper_skill"] != undefined) {
                        upper_skill.innerText = skill_name_obj["upper_skill"];
                        upper_skill_title.parentElement!.parentElement!.style.display = "table-row";
                    } else {
                        upper_skill_title.parentElement!.parentElement!.style.display = "none";
                    }
                    // lower_skill
                    if (skill_name_obj["lower_skill"] != undefined) {
                        lower_skill.innerText = skill_name_obj["lower_skill"];
                        lower_skill_title.parentElement!.parentElement!.style.display = "table-row";
                    } else {
                        lower_skill_title.parentElement!.parentElement!.style.display = "none";
                    }



                    // ========== enhance_skill_data ========== //
                    let enhance_skill_data = null;
                    switch (Config.GameServer)
                    {
                    case GameServer.JP:
                        switch (Config.JpServerLanguage)
                        {
                        case JpServerLanguage.JP:
                            enhance_skill_data = enhance_skill_data_jp;
                            break;
                        case JpServerLanguage.TW:
                            enhance_skill_data = enhance_skill_data_jp;
                            break;
                        }
                        break;
                    case GameServer.TW:
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

                            createSkillLabel(
                                skill_data_type as SkillDataType,
                                skill_data_title,
                                skill_data_data
                            );
                        }
                    }
                }
            }
        }
    }

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

    
    if (rect.left + skill_table_size.width > windowWidth)
    {
        // console.log("超出視窗外！")
        // console.log("width: " + content_width, "height: " + content_height);
        // console.log("left: " + rect.left, "right: " + rect.right);
        let horizontal_offset = (rect.left + skill_table_size.width) - windowWidth + 17;
        
        skill_hint_content.style.left = parseInt(skill_hint_content.style.left) - horizontal_offset + "px";
        skill_hint_content.style.right = parseInt(skill_hint_content.style.right) - horizontal_offset + "px";
    }
    if (rect.top + skill_table_size.height > windowHeight)
    {
        // console.log("超出視窗外！")

        let vertical_offset = (rect.top + skill_table_size.height) - windowHeight;

        
        skill_hint_content.style.top = parseInt(skill_hint_content.style.top) - vertical_offset + "px";
        skill_hint_content.style.bottom = parseInt(skill_hint_content.style.bottom) - vertical_offset + "px";
    }

    // console.log(skill_table_size.width, skill_table_size.height);

    // skill_hint_content.style.width = parseInt(skill_table_size.width) + "px";
    skill_hint_content.style.height = parseInt(skill_table_size.height) + "px";
}

function updateSkillContent(): void
{
    const skill_hint_content = document.getElementById("skill_hint_content")!;
    let skill_hint_elements = document.querySelectorAll(".skill_hint");
    for (let i = 0; i < skill_hint_elements.length; i++) {
        const skill_hint = skill_hint_elements[i] as HTMLSpanElement;

        if (isMobileDevice())
        {
            skill_hint.style.fontSize = "1.2em"

            skill_hint.addEventListener("touchstart", (event) => {
                findSkillData(event, skill_hint);
            });
            skill_hint.addEventListener("touchend", (event) => {
                skill_hint_content.style.display = "none";
            });
        }
        else
        {
            skill_hint.addEventListener("mouseenter", (event) => {
                findSkillData(event, skill_hint);
            });
            skill_hint.addEventListener("mouseleave", (event) => {
                skill_hint_content.style.display = "none";
            });    
        }
    }
}

function hideSkillHintContent(): void
{
    const skill_hint_content = document.getElementById("skill_hint_content")!;
    skill_hint_content.style.display = "none";
}

// ======================================================================================================

if (!isMobileDevice())
{
    readJson("../UmaData/skill_data_jp.json", (jsonData: string | null) => {
        skill_data_jp = jsonData;
    });
    
    readJson("../UmaData/skill_data_tw.json", (jsonData: string | null) => {
        skill_data_tw = jsonData;
    });
    
    readJson("../UmaData/skill_data_jp_trans_tw.json", (jsonData: string | null) => {
        skill_data_jp_trans_tw = jsonData;
    });
    
    readJson("../UmaData/enhance_skill_data_jp.json", (jsonData: string | null) => {
        enhance_skill_data_jp = jsonData;
    });
    
    readJson("../UmaData/enhance_skill_data_tw.json", (jsonData: string | null) => {
        enhance_skill_data_tw = jsonData;
    });    
}


updateSkillContent();