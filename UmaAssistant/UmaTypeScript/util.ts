/**
 * 給Java調用的函式，把 Java 的 json 物件設置到 json_data.js 的變數中
 * @param {string} dataVariableName - json 資料的變數名稱 
 * @param {string} value - 要設置的 json 資料
 */
function setJsonData(dataVariableName: string, value: string): void
{
    switch (dataVariableName)
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

/**
 * Windows 從本地伺服器讀取 json
 * @param {string} jsonPath - .json 的路徑
 * @param {Function} callback - 回調函式，會回傳帶有 jsonData 參數的函式
 */
function readJson(jsonPath: string, callback: Function): void
{
    const READY_STATE_DONE = 4; // 資料接收完畢
    const STATUS_SUCCESS = 200; // 請求成功

    let xhr = new XMLHttpRequest();

    xhr.onreadystatechange = function() {
        if (xhr.readyState === READY_STATE_DONE)
        {
            if (xhr.status === STATUS_SUCCESS)
            {
                // 解析 JSON
                let jsonData: string = JSON.parse(xhr.responseText);
                callback(jsonData);
            }
            else
            {
                console.error('readJson Error:', xhr.statusText);
            }
        }
    };
    
    xhr.open('GET', jsonPath, true);
    xhr.send();
}


/**
 * 是否為行動裝置
 * @returns {boolean}
 */
function isMobileDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/android|webos|iphone|ipad|ipod|blackberry|windows phone/i)) ? true : false;
}

/**
 * 檢查目前裝置是否為 Android
 * @returns {boolean}
 */
function isAndroidDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/android/i)) ? true : false;
}

/**
 * 檢查目前裝置是否為 Windows
 * @returns {boolean}
 */
function isWindowsDevice(): boolean
{
    return (navigator.userAgent.toLowerCase().match(/windows/i)) ? true : false;
}

/**
 * 平仮名を片仮名に変換する
 * @param hiragana - 平仮名
 * @returns {string} 片仮名
 */
function hiraganaToKatakana(hiragana: string): string
{
    return hiragana.replace(/[\u3041-\u3096]/g, (match) => {
        let chr = match.charCodeAt(0) + 0x60;
        return String.fromCharCode(chr);
    });
}

/**
 * 獲取 element 的 width 和 height
 * @param {Element} element 
 * @returns {Object} 
 */
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

/**
 * 禁用滑鼠右鍵開啟選單
 */
function disableContextMenu(): void
{
    document.addEventListener("contextmenu", (e) => { e.preventDefault(); }, false);
}