#pragma once

#include "sead/prim/seadSafeString.h"

#include "cjson/cJSON.h"

struct UpdateApiInfo {
    UpdateApiInfo(cJSON* json, const cJSON* tagName);

    sead::FixedSafeString<0x20> mName;
    sead::FixedSafeString<0x20> mTagName;
    sead::FixedSafeString<0x20> mAuthorName;
    sead::FixedSafeString<0x20> mPublishDate;
    bool mIsPrerelease = false;
};