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
    char_img.loading = "lazy";

    char_img.onclick = function() {
        console.log(char_img.alt);
    }


    icon_container.appendChild(char_img);
}

function toKatakana(text) {
    return text.replace(/[\u3041-\u3096]/g, function(match) {
        let chr = match.charCodeAt(0) + 0x60;
        return String.fromCharCode(chr);
    });
}

function setSearchTextbox() {
    const search_textbox = document.getElementById("search_textbox");
    
    search_textbox.addEventListener("input", function() {
        let pattern = new RegExp(search_textbox.value + "|" + toKatakana(search_textbox.value), "i");

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

function reflushCharacterElement() {
    if (select_character_data == null) return;
    for (let idx in select_character_data) {
        const item = select_character_data[idx];
        // console.log("Icon:", item.icon);
        // console.log("JP Event Owner:", item.jp_event_owner);
        // console.log("TW Event Owner:", item.tw_event_owner);
        createCharacterImageButton(item.jp_event_owner, item.tw_event_owner, item.icon);
    }
}

let select_character_data = null;

readJson("../UmaData/select_character_data.json", function(jsonData) {
    select_character_data = jsonData;
});

function LoadData() {
    if (select_character_data === null) {
        // console.log("Loading...");
        setTimeout(LoadData, 100);
    } else {
        // console.log("Loaded Data!");
        reflushCharacterElement();
    }
}

LoadData();

setSearchTextbox();


// createCharacterButton("オグリキャップ");
// createCharacterButton("トウカイテイオー");
// createCharacterButton("キタサンブラック");