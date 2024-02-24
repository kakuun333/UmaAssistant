// Java 的 json 物件設置到 json_data.js 的變數中
function setJsonData(variableName: string, value: string): void
{
    switch (variableName)
    {
    case JsonDataType.SKILL_DATA_JP:
        skill_data_jp = value;
        break;
    case JsonDataType.SKILL_DATA_TW:
        skill_data_tw = value;
        break;
    case JsonDataType.SKILL_DATA_TW:
        skill_data_jp_trans_tw = value;
        break;
    case JsonDataType.ENHANCE_SKILL_DATA_JP:
        enhance_skill_data_jp = value;
        break;
    case JsonDataType.ENHANCE_SKILL_DATA_TW:
        enhance_skill_data_tw = value;
        break;
    case JsonDataType.SELECT_CHARACTER_DATA:
        select_character_data = value;
        break;
    }
}

// Windows 從本地伺服器讀取 json
function readJson(jsonPath: string, callback: Function): void
{
    const READY_STATE_DONE = 4; // 資料接收完畢
    const STATUS_SUCCESS = 200; // 請求成功

    let xhr = new XMLHttpRequest();

    xhr.onreadystatechange = function() {
        if (xhr.readyState === READY_STATE_DONE) {
            if (xhr.status === STATUS_SUCCESS) {
                // 解析 JSON
                let jsonData: string = JSON.parse(xhr.responseText);
                callback(jsonData);
            } else {
                console.error('readJson Error:', xhr.statusText);
            }
        }
    };
    
    xhr.open('GET', jsonPath, true);
    xhr.send();
}

// 是否為行動裝置
function isMobileDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/android|webos|iphone|ipad|ipod|blackberry|windows phone/i)) ? true : false;
}

function isAndroidDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/android/i)) ? true : false;
}

function isWindowsDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/windows/i)) ? true : false;
}

// 平仮名を片仮名に変換する
function hiraganaToKatakana(hiragana: string): string
{
    return hiragana.replace(/[\u3041-\u3096]/g, (match) => {
        let chr = match.charCodeAt(0) + 0x60;
        return String.fromCharCode(chr);
    });
}

// 獲取 element 的 width 和 height
function getSize(element: Element): any
{
    let _rect = element.getBoundingClientRect();
    let _width = _rect.right - _rect.left;
    let _height = _rect.bottom - _rect.top;

    const tmp = {
        width: _width,
        height: _height
    }

    return tmp;
}

// 禁用滑鼠右鍵
function disableContextMenu(): void
{
    document.addEventListener("contextmenu", (e) => { e.preventDefault(); }, false);
}