function changeCharacterName(characterName) {
    let character_name = document.getElementById("character_name");

    character_name.innerHTML = characterName;

    const SINGLE_LINE_MAX_TEXT_LENGTH = 20;

    character_name.style.fontSize = "1em";
    if (characterName.length > SINGLE_LINE_MAX_TEXT_LENGTH)
    {
        let currentLength = characterName.length - SINGLE_LINE_MAX_TEXT_LENGTH;

        const computedStyle = window.getComputedStyle(character_name);
        const MIN_PERCENTAGE = 0.01
        let decrease_percentage = 0.065;
        let fontSize = computedStyle.fontSize;


        for (let i = 0; i < currentLength; ++i)
        {
            const char = characterName[i];

            fontSize = parseFloat(fontSize) - (parseFloat(fontSize) * decrease_percentage);

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
            console.log(fontSize);

            --currentLength;

            
        
            // console.log(`${char} 是${isFullWidth ? '全角' : '半角'}`);
        }
    }
}

function changeCharacterNameBrowserLang(softwareLang) {
    let character_name_title = document.getElementById("character_name_title");

    const JP = 0;
    const TW = 1;

    switch (softwareLang) {
    case TW:
        character_name_title.innerHTML = "目前培育的馬娘";
        character_name_title.style.fontSize = "0.9em";
        break;
    case JP:
        character_name_title.innerHTML = "育成しているウマ娘";
        character_name_title.style.fontSize = "0.88em";
        break;
    }
}
