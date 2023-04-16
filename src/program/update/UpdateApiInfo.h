#pragma once

#include "sead/prim/seadSafeString.h"

#include "cjson/cJSON.h"

struct UpdateApiInfo {
    UpdateApiInfo(cJSON* json, const cJSON* tagName);

    sead::FixedSafeString<0x40> mName;
    sead::FixedSafeString<0x10> mTagName;
    sead::FixedSafeString<0x20> mAuthorName;
    sead::FixedSafeString<0x10> mPublishDate;
    bool mIsPrerelease = false;
};