// 創建 choice
function createChoice(choice_name, choice_effect) {

    if (isAndroidDevice()) {
        choice_name = decodeURIComponent(choice_name);
        choice_effect = decodeURIComponent(choice_effect);
    }

    const choice_table = document.getElementById("choice_table");
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

function changeEventName(text) {

    if (isAndroidDevice()) text = decodeURIComponent(text);

    const event_name = document.getElementById("event_name");
    event_name.innerHTML = text;
}

function changeEventOwner(text) {

    if (isAndroidDevice()) text = decodeURIComponent(text);

    const event_owner = document.getElementById("event_owner");
    event_owner.innerHTML = text;
}

// 清除所有選項
function cleanChoiceTable() {
    const choice_table = document.getElementById("choice_table");
    while (choice_table.firstChild) {
        choice_table.removeChild(choice_table.firstChild);
    }
}

function changeChoiceHtmlLanguage(language) {
    // event_owner
    const event_owner_title = document.getElementById("event_owner_title");
    // event_name
    const event_name_title = document.getElementById("event_name_title");
    // skill_content
    const skill_pt_title = document.getElementById("skill_pt_title");
    const skill_description_title = document.getElementById("skill_description_title");
    const upper_skill_title = document.getElementById("upper_skill_title");
    const lower_skill_title = document.getElementById("lower_skill_title");
    // skill_effect
    const skill_effect_title = document.getElementById("skill_effect_title");
    const skill_condition_title = document.getElementById("skill_condition_title");

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

function test(one, two, three)
{
    str = `one:${one.toString()}, two:${two.toString()}, three:${three.toString()}`
    alert(str);
}

window.onload = function() {
    window.chrome.webview.postMessage("Hello from JavaScript!");
};

// function setCustomScroll() {
//     let content = document.getElementById("content");
//     let custom_scroll = document.getElementById("custom_scroll");
//     let isMouseDown = false;
//     let startX, startY;


//     // 初始化 custom_scroll 的 top
//     custom_scroll.style.top = "1px";



//     custom_scroll.addEventListener('mousedown', function(event) {
//         if (event.button === 0) { // 滑鼠左鍵
//             console.log("down");

//             isMouseDown = true;
//             startX = event.clientX;
//             startY = event.clientY;
//             event.preventDefault();
//         }
//     });

//     window.addEventListener('mousemove', function(event) {
//         if (isMouseDown) {
//             let deltaX = event.clientX - startX;
//             let deltaY = event.clientY - startY;

//             // 調整 window 的滾輪位置
//             window.scrollBy({
//                 top: deltaY,
//                 left: deltaX,
//                 behavior: "auto" // 可以使用 auto 或 smooth 控制滾輪行為
//             });

//             let currentTop = parseInt(custom_scroll.style.top) || 0;
//             custom_scroll.style.top = currentTop + deltaY + "px";

//             console.log(event.clientX);


//             startX = event.clientX;
//             startY = event.clientY;
//         }
//     });

//     window.addEventListener('mouseup', function(event) {
//         if (event.button === 0) {
//             console.log("up");
//             isMouseDown = false;
//         }
//     });

//     window.addEventListener("change", function(event) {
//         console.log(event);
//     })

//     window.addEventListener('resize', function() {
//         let documentHeight = document.documentElement.scrollHeight;
//         let viewportHeight = window.innerHeight;

//         scrollBarHeight = (viewportHeight / documentHeight) * 100;
//         custom_scroll.style.height = scrollBarHeight + "%";
//     });
// }
// setCustomScroll();


/* 監聽滾輪事件 */
// content.addEventListener('wheel', function(event) {
//     // 獲取滾動方向和速度
//     let delta = event.deltaY || event.detail || event.wheelDelta;
//     let scrollYPos = window.scrollY || window.pageYOffset;

//     let documentHeight = document.documentElement.scrollHeight;
//     let viewportHeight = window.innerHeight;
//     let scrollRange = documentHeight - viewportHeight;

//     const scrollValue = scrollRange / 3;

//     if (delta > 0) {
//         // 向下滚動
//         window.scroll(0, scrollYPos + scrollValue);
//     } else {
//         // 向上滚動
//         window.scroll(0, scrollYPos - scrollValue);
//     }

//     // 更新 custom_scroll 的位置
//     let scrollPersent = (scrollYPos / scrollRange) * 100;
//     let scrollTop = Math.min(scrollPersent, 85);
//     // custom_scroll.style.top = scrollTop + "%";
//     // console.log("top", custom_scroll.style.top);
//     console.log("scrollYPos", scrollYPos);
//     console.log('viewportHeight', viewportHeight);
//     console.log('scrollRange', scrollRange);
// });

// createChoice("title", "effect<br>effect");
// createChoice("title", "effect<br>effect");


