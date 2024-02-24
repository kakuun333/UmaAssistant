"use strict";
// Android 版本的軟體語言
var AndroidLocale;
(function (AndroidLocale) {
    AndroidLocale["JP"] = "ja";
    AndroidLocale["TW"] = "zh";
    AndroidLocale["EN"] = "en";
})(AndroidLocale || (AndroidLocale = {}));
// Windows 版本的軟體語言
var SoftwareLanguage;
(function (SoftwareLanguage) {
    SoftwareLanguage[SoftwareLanguage["JP"] = 0] = "JP";
    SoftwareLanguage[SoftwareLanguage["TW"] = 1] = "TW";
    SoftwareLanguage[SoftwareLanguage["EN"] = 2] = "EN";
})(SoftwareLanguage || (SoftwareLanguage = {}));
var GameServer;
(function (GameServer) {
    GameServer[GameServer["JP"] = 0] = "JP";
    GameServer[GameServer["TW"] = 1] = "TW";
})(GameServer || (GameServer = {}));
var JpServerLanguage;
(function (JpServerLanguage) {
    JpServerLanguage[JpServerLanguage["JP"] = 0] = "JP";
    JpServerLanguage[JpServerLanguage["TW"] = 1] = "TW";
})(JpServerLanguage || (JpServerLanguage = {}));
var JsonDataType;
(function (JsonDataType) {
    JsonDataType["EVENT_DATA_JP"] = "event_data_jp";
    JsonDataType["EVENT_DATA_TW"] = "event_data_tw";
    JsonDataType["SKILL_DATA_JP"] = "skill_data_jp";
    JsonDataType["SKILL_DATA_TW"] = "skill_data_tw";
    JsonDataType["SKILL_DATA_JP_TRANS_TW"] = "skill_data_jp_trans_tw";
    JsonDataType["ENHANCE_SKILL_DATA_JP"] = "enhance_skill_data_jp";
    JsonDataType["ENHANCE_SKILL_DATA_TW"] = "enhance_skill_data_tw";
    JsonDataType["SELECT_CHARACTER_DATA"] = "select_character_data";
})(JsonDataType || (JsonDataType = {}));
var MessageType;
(function (MessageType) {
    MessageType["CHARACTER_IMAGE_CLICK"] = "charImgClick";
    MessageType["SAVE_RACE_SCHEDULE_DATA"] = "saveRaceScheduleData";
})(MessageType || (MessageType = {}));
var UmaColor;
(function (UmaColor) {
    UmaColor["UMA_BLUE"] = "rgb(85, 118, 120)";
    UmaColor["UMA_DARK_PURPLE"] = "rgb(107, 85, 136)";
})(UmaColor || (UmaColor = {}));
var SkillDataType;
(function (SkillDataType) {
    SkillDataType["SKILL_EFFECT"] = "skill_effect";
    SkillDataType["SKILL_CONDITION"] = "skill_condition";
})(SkillDataType || (SkillDataType = {}));
