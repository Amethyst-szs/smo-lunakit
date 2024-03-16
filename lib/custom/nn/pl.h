#pragma once

#include "types.h"

namespace nn::pl
{

    enum SharedFontType {
        STANDARD = 0x00, //	Japan, US and Europe (Standard)
        CHINESE_SIMPLIFIED = 0x01, //	Chinese Simplified
        EXT_CHINESE_SIMPLIFIED = 0x02, //	Extended Chinese Simplified
        CHINESE_TRAD = 0x03, //	Chinese Traditional
        KOREAN = 0x04, //	Korean (Hangul)
        NN_EXT = 0x05 //	Nintendo Extended
    };

    enum LoadState { LOADING, LOADED };

    bool GetSharedFontLoadState(SharedFontType);
    void *GetSharedFontAddress(SharedFontType);
    u32 GetSharedFontSize(SharedFontType);	
} // namespace nn::pl
