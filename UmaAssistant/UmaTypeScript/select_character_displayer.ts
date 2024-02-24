function createCharacterImageButton(jp_event_owner: string, tw_event_owner: string, img_name: string): void
{
    const icon_container = document.getElementById("icon_container")!;

    const char_img = document.createElement("img");

    char_img.className = "character_icon";
    /*
    IE 瀏覽器不支持語法
    char_img.src = `../UmaMisc/Image/Character/${img_name}`;
    */ 
    char_img.src = `../UmaMisc/Image/Character/${img_name}`;
    char_img.alt = `<jp_event_owner>${jp_event_owner}</jp_event_owner><tw_event_owner>${tw_event_owner}</tw_event_owner>`;
    // char_img.alt = "<jp_event_owner>"+jp_event_owner+"</jp_event_owner>"+"<tw_event_owner>"+tw_event_owner+"</tw_event_owner>";
    char_img.loading = "eager";
    char_img.draggable = false;

    char_img.addEventListener("load", () => {
        char_img.style.display = "inline";
    });

    if (isAndroidDevice())
    {
        char_img.addEventListener("click", function(event)
        {
            // @ts-ignore
            Android.onCharacterIconClick(char_img.src, char_img.alt);
        });
    }
    else if (isWindowsDevice())
    {
        char_img.addEventListener("click", function(event)
        {
            const msgObj = {
                messageType: "charImgClick",
                src: char_img.src,
                alt: char_img.alt,
            }

            // @ts-ignore
            window.chrome.webview.postMessage(JSON.stringify(msgObj));
        });
    }
    
    icon_container.appendChild(char_img);
}

function setSearchTextbox(): void
{
    const search_title = document.getElementById("search_title")!;
    const search_textbox = document.getElementById("search_textbox")! as HTMLInputElement;

    if (isMobileDevice())
    {
        search_title.style.height = "10vh";
        search_textbox.parentElement!.style.height = "10vh";
    }
    
    search_textbox.addEventListener("input", () => {
        let pattern = new RegExp(search_textbox.value + "|" + hiraganaToKatakana(search_textbox.value), "i");

        let character_icon_elements = document.querySelectorAll(".character_icon");

        for (let i = 0; i < character_icon_elements.length; i++)
        {
            let character_icon = character_icon_elements[i] as HTMLImageElement;
            if (character_icon.alt.match(pattern))
            {
                character_icon.style.display = "inline";
            }
            else
            {
                character_icon.style.display = "none";
            }
        }
    });
}


function reflushCharacterElement(): void
{
    if (select_character_data == null) return;

    for (let idx in select_character_data)
    {
        const item = select_character_data[idx];
        createCharacterImageButton(item.jp_event_owner, item.tw_event_owner, item.icon);
    }
}

function changeSelectCharacterHtmlLanguage(language: SoftwareLanguage | AndroidLocale)
{
    const search_title = document.getElementById("search_title")!;
    const search_textbox = document.getElementById("search_textbox")! as HTMLInputElement;

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


function loadSelectCharacterData(): void
{
    if (select_character_data === null)
    {
        console.log("Loading select_character_data...");
        setTimeout(loadSelectCharacterData, 100);
    }
    else
    {
        console.log("Loaded select_character_data !!");
        reflushCharacterElement();
    }
}

function setImgAlign(): void
{
    const icon_container = document.getElementById("icon_container")!;

    if (isMobileDevice())
    {
        icon_container.style.textAlign = "center";
    }
    else
    {
        icon_container.style.textAlign = "left";
    }
}


// ======================================================================================================

if (isWindowsDevice())
{
    readJson("../UmaData/select_character_data.json", (jsonData: string | null) => {
        select_character_data = jsonData;
    });
}

setImgAlign();
loadSelectCharacterData();
setSearchTextbox();
disableContextMenu();