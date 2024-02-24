function changeCharacterName(characterName: string): void {
    const character_name = document.getElementById("character_name")!;

    character_name.innerHTML = characterName;

    const SINGLE_LINE_MAX_TEXT_LENGTH = 20;

    character_name.style.fontSize = "1em";
    if (characterName.length > SINGLE_LINE_MAX_TEXT_LENGTH)
    {
        let currentLength = characterName.length - SINGLE_LINE_MAX_TEXT_LENGTH;

        const computedStyle = window.getComputedStyle(character_name);
        const MIN_PERCENTAGE = 0.01
        let decrease_percentage = 0.065;
        let fontSize: string = computedStyle.fontSize;


        for (let i = 0; i < currentLength; i++)
        {
            const char = characterName[i];

            fontSize = (parseFloat(fontSize) - (parseFloat(fontSize) * decrease_percentage)).toString();

            // 用正規表達式判断是否為全形字符
            const IS_FULL_WIDTH = /[^\x00-\x7F]/.test(char);
            
            switch (IS_FULL_WIDTH)
            {
            case true:
                decrease_percentage = decrease_percentage > MIN_PERCENTAGE ? decrease_percentage - 0.01 : 0.01;
                break;
            case false:
                decrease_percentage = decrease_percentage > MIN_PERCENTAGE ? decrease_percentage - 0.02 : 0.02;
                break;
            }

            character_name.style.fontSize = fontSize + "px";
            --currentLength;
        }
    }
}

function changeCharacterNameHtmlLanguage(language: SoftwareLanguage | AndroidLocale) {
    const character_name_title = document.getElementById("character_name_title")!;
    
    if (language == SoftwareLanguage.JP || language == AndroidLocale.JP)
    {
        character_name_title.innerHTML = "育成ウマ娘";
        character_name_title.style.fontSize = "0.88em";
    }
    else if (language == SoftwareLanguage.TW || language == AndroidLocale.TW)
    {
        character_name_title.innerHTML = "培育馬娘";
        character_name_title.style.fontSize = "0.9em";
    }
    else if (language == SoftwareLanguage.EN || language == AndroidLocale.EN)
    {
        character_name_title.innerHTML = "Training Umamusume";
        character_name_title.style.fontSize = "0.7em";
    }
}


disableContextMenu();