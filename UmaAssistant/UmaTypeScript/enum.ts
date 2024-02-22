// Android 版本的軟體語言
export enum AndroidLocale
{
    JP = "ja",
    TW = "zh",
    EN = "en",
}

// Windows 版本的軟體語言
export enum SoftwareLanguage
{
    JP = 0,
    TW = 1,
    EN = 2
}

export enum GameServer
{
    JP = 0,
    TW = 1,
}

export enum JpServerLanguage
{
    JP = 0,
    TW = 1,
}

export enum JsonDataType
{
    EVENT_DATA_JP = "event_data_jp",
    EVENT_DATA_TW = "event_data_tw",

    SKILL_DATA_JP = "skill_data_jp",
    SKILL_DATA_TW = "skill_data_tw",
    SKILL_DATA_JP_TRANS_TW = "skill_data_jp_trans_tw",

    ENHANCE_SKILL_DATA_JP = "enhance_skill_data_jp",
    ENHANCE_SKILL_DATA_TW = "enhance_skill_data_tw",

    SELECT_CHARACTER_DATA = "select_character_data",
}

export enum MessageType
{
    CHARACTER_IMAGE_CLICK = "charImgClick"
}