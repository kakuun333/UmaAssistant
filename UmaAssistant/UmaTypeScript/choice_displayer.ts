// 創建 choice
function createChoice(choice_name: string, choice_effect: string) {

    if (isAndroidDevice()) {
        choice_name = decodeURIComponent(choice_name);
        choice_effect = decodeURIComponent(choice_effect);
    }

    const choice_table = document.getElementById("choice_table")!;
    let title_tr = document.createElement("tr");
    let th = document.createElement("th");
    // ------------------------------------------ //
    th.innerHTML = choice_name;
    th.className = "choice_name";
    title_tr.appendChild(th);
    choice_table.appendChild(title_tr);

    // ------------------------------------------ //
    let effect_tr = document.createElement("tr");
    let td = document.createElement("td");
    
    // ------------------------------------------ //
    td.innerHTML = choice_effect;
    td.className = "choice_effect";
    effect_tr.appendChild(td);
    choice_table.appendChild(effect_tr);

    // ------------------------------------------ //
    // let hr = document.createElement("hr");
    // choice_table.appendChild(hr);
}

function changeEventName(text: string) {

    if (isAndroidDevice()) text = decodeURIComponent(text);

    const event_name = document.getElementById("event_name")!;
    event_name.innerHTML = text;
}

function changeEventOwner(text: string) {

    if (isAndroidDevice()) text = decodeURIComponent(text);

    const event_owner = document.getElementById("event_owner")!;
    event_owner.innerHTML = text;
}

// 清除所有選項
function cleanChoiceTable() {
    const choice_table = document.getElementById("choice_table")!;
    while (choice_table.firstChild) {
        choice_table.removeChild(choice_table.firstChild);
    }
}

function changeChoiceHtmlLanguage(language: SoftwareLanguage | AndroidLocale) {
    // event_owner
    const event_owner_title = document.getElementById("event_owner_title")!;
    // event_name
    const event_name_title = document.getElementById("event_name_title")!;
    // skill_content
    const skill_pt_title = document.getElementById("skill_pt_title")!;
    const skill_description_title = document.getElementById("skill_description_title")!;
    const upper_skill_title = document.getElementById("upper_skill_title")!;
    const lower_skill_title = document.getElementById("lower_skill_title")!;
    // skill_effect
    const skill_effect_title = document.getElementById("skill_effect_title")!;
    const skill_condition_title = document.getElementById("skill_condition_title")!;

    if (language == SoftwareLanguage.JP || language == AndroidLocale.JP)
    {
        // event_owner
        event_owner_title.innerHTML = "イベント所有者";
        // event_name
        event_name_title.innerHTML = "イベント";
        // skill_content
        skill_pt_title.innerHTML = "スキルpt";
        skill_description_title.innerHTML = "説明文";
        upper_skill_title.innerHTML = "上位スキル";
        lower_skill_title.innerHTML = "下位スキル";
        // skill_effect
        skill_effect_title.innerHTML = "効果";
        skill_condition_title.innerHTML = "発動条件";
    }
    else if (language == SoftwareLanguage.TW || language == AndroidLocale.TW)
    {
        // event_owner
        event_owner_title.innerHTML = "事件所有者";
        // event_name
        event_name_title.innerHTML = "事件名稱";
        // skill_content
        skill_pt_title.innerHTML = "所需技能點";
        skill_description_title.innerHTML = "描述";
        upper_skill_title.innerHTML = "上位技能";
        lower_skill_title.innerHTML = "下位技能";
        // skill_effect
        skill_effect_title.innerHTML = "效果";
        skill_condition_title.innerHTML = "發動條件";
    }
    else if (language == SoftwareLanguage.EN || language == AndroidLocale.EN)
    {
        // event_owener
        event_owner_title.innerHTML = "Event Owner";
        // event_name
        event_name_title.innerHTML = "Event Name";
        // skill_content
        skill_pt_title.innerHTML = "Skill Point";
        skill_description_title.innerHTML = "Description";
        upper_skill_title.innerHTML = "Upper-level Skill";
        lower_skill_title.innerHTML = "Lower-level Skill";
        // skill_effect
        skill_effect_title.innerHTML = "Effect";
        skill_condition_title.innerHTML = "Cast Condition";
    }
}

// 根據裝置類型調整 userSelect
// 只有 Windows 可以選取文字
if (isWindowsDevice())
{
    document.body.style.userSelect = "text";
}
else
{
    document.body.style.userSelect = "none";
}

disableContextMenu();