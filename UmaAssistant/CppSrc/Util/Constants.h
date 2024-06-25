#pragma once

namespace util
{
    constexpr inline unsigned int UTF8_CHAR_BYTE = 0x3; // 一個 utf8 文字佔的 Byte 數量
    constexpr inline float SIMILAR_METRIC = 50;         // 相似度標準，大於 SIMILAR_METRIC 才算是相似;
    constexpr inline float JP_CHAR_SIMILAR_METRIC = 65;
    constexpr inline int MAX_SIMIALARITY = 100;
    constexpr inline int NOT_SIMILAR = -1;
};
