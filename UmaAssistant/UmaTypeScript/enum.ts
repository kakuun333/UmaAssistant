/**
 * Android 系統語言類型
 */
enum AndroidLocale
{
    JP = "ja",
    TW = "zh",
    EN = "en",
}

/**
 * Windows 版本的軟體語言
 */
enum SoftwareLanguage
{
    JP = 0,
    TW = 1,
    EN = 2
}

/**
 * 遊戲伺服器類型
 */
enum GameServer
{
    JP = 0,
    TW = 1,
}

enum JpServerLanguage
{
    JP = 0,
    TW = 1,
}

enum JsonDataType
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

/**
 * WebMassage 的類型
 */
enum MessageType
{
    CHARACTER_IMAGE_CLICK = "charImgClick",
    SAVE_RACE_SCHEDULE_DATA = "saveRaceScheduleData",
    LOAD_RACE_SCHEDULE_DATA = "loadRaceScheduleData"
}

enum UmaColor
{
    UMA_BLUE = "rgb(85, 118, 120)",
    UMA_DARK_PURPLE = "rgb(107, 85, 136)"
}

enum SkillDataType
{
    SKILL_EFFECT = "skill_effect",
    SKILL_CONDITION = "skill_condition"
}