function changeCharacterName(characterName) {
    let character_name = document.getElementById("character_name");

    character_name.innerHTML = characterName;
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
