function createCharacterImageButton(jp_event_owner, tw_event_owner, img_name) {
    const icon_container = document.getElementById("icon_container");

    const char_img = document.createElement("img");

    char_img.className = "character_icon";
    /*
    IE 瀏覽器不支持語法
    char_img.src = `../UmaMisc/Image/Character/${img_name}`;
    */ 
    char_img.src = "../UmaMisc/Image/Character/" + img_name;
    char_img.alt = "<jp_event_owner>"+jp_event_owner+"</jp_event_owner>"+"<tw_event_owner>"+tw_event_owner+"</tw_event_owner>";
    char_img.loading = "eager";

    char_img.addEventListener("load", function() {
        char_img.style.display = "inline";
    });

    if (isAndroidDevice())
    {
        char_img.addEventListener("click", function(event) {
            Android.onCharacterIconClick(char_img.src, char_img.alt);
        });
    }
    else if (isWindowsDevice())
    {
        char_img.addEventListener("click", function(event) {
            const msgObj = {
                messageName: "charImgClick",
                src: char_img.src,
                alt: char_img.alt,
            }
            window.chrome.webview.postMessage(JSON.stringify(msgObj));
        });
    }
    
    icon_container.appendChild(char_img);
}

function setSearchTextbox() {
    const search_title = document.getElementById("search_title");
    const search_textbox = document.getElementById("search_textbox");

    if (isMobileDevice()) {
        search_title.style.height = "10vh";
        search_textbox.parentElement.style.height = "10vh";
    }
    
    search_textbox.addEventListener("input", function() {
        let pattern = new RegExp(search_textbox.value + "|" + hiraganaToKatakana(search_textbox.value), "i");

        let character_icon_elements = document.querySelectorAll(".character_icon");

        for (let i = 0; i < character_icon_elements.length; i++) {
            let character_icon = character_icon_elements[i];
            if (character_icon.alt.match(pattern)) {
                character_icon.style.display = "inline";
            } else {
                character_icon.style.display = "none";
            }
        }
    });
}


function reflushCharacterElement() {
    if (select_character_data == null) return;
    for (let idx in select_character_data) {
        const item = select_character_data[idx];
        createCharacterImageButton(item.jp_event_owner, item.tw_event_owner, item.icon);
    }
}

function changeSelectCharacterHtmlLanguage(language) {
    const search_title = document.getElementById("search_title");
    const search_textbox = document.getElementById("search_textbox");

    if (language == SoftwareLanguage.JP || language == AndroidLocale.JP)
    {
        search_title.innerHTML = "キャラ検索";
        search_textbox.placeholder = "クリックで検索";
    }
    else if (language == SoftwareLanguage.TW || language == AndroidLocale.TW)
    {
        search_title.innerHTML = "角色査詢";
        search_textbox.placeholder = "點擊此處輸入角色名稱";
    }
    else if (language == SoftwareLanguage.EN || language == AndroidLocale.EN)
    {
        search_title.innerHTML = "Search Character";
        search_textbox.placeholder = "Click to search character";
    }
}


function loadSelectCharacterData() {
    if (select_character_data === null) {
        console.log("Loading select_character_data...");
        setTimeout(loadSelectCharacterData, 100);
    } else {
        console.log("Loaded select_character_data !!");
        reflushCharacterElement();
    }
}

function setImgAlign() {
    const icon_container = document.getElementById("icon_container");

    if (isMobileDevice()) {
        icon_container.style.textAlign = "center";
    } else {
        icon_container.style.textAlign = "left";
    }
}


// ======================================================================================================

if (isWindowsDevice()) {
    readJson("../UmaData/select_character_data.json", function(jsonData) {
        select_character_data = jsonData;
    });
}

setImgAlign();
loadSelectCharacterData();
setSearchTextbox();