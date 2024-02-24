"use strict";
// Java 的 json 物件設置到 json_data.js 的變數中
function setJsonData(variableName, value) {
    switch (variableName) {
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
function readJson(jsonPath, callback) {
    var READY_STATE_DONE = 4; // 資料接收完畢
    var STATUS_SUCCESS = 200; // 請求成功
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (xhr.readyState === READY_STATE_DONE) {
            if (xhr.status === STATUS_SUCCESS) {
                // 解析 JSON
                var jsonData = JSON.parse(xhr.responseText);
                callback(jsonData);
            }
            else {
                console.error('readJson Error:', xhr.statusText);
            }
        }
    };
    xhr.open('GET', jsonPath, true);
    xhr.send();
}
// 是否為行動裝置
function isMobileDevice() {
    return (navigator.userAgent.toLowerCase().match(/android|webos|iphone|ipad|ipod|blackberry|windows phone/i)) ? true : false;
}
function isAndroidDevice() {
    return (navigator.userAgent.toLowerCase().match(/android/i)) ? true : false;
}
function isWindowsDevice() {
    return (navigator.userAgent.toLowerCase().match(/windows/i)) ? true : false;
}
// 平仮名を片仮名に変換する
function hiraganaToKatakana(hiragana) {
    return hiragana.replace(/[\u3041-\u3096]/g, function (match) {
        var chr = match.charCodeAt(0) + 0x60;
        return String.fromCharCode(chr);
    });
}
// 獲取 element 的 width 和 height
function getSize(element) {
    var _rect = element.getBoundingClientRect();
    var _width = _rect.right - _rect.left;
    var _height = _rect.bottom - _rect.top;
    var tmp = {
        width: _width,
        height: _height
    };
    return tmp;
}
// 禁用滑鼠右鍵
function disableContextMenu() {
    document.addEventListener("contextmenu", function (e) { e.preventDefault(); }, false);
}
