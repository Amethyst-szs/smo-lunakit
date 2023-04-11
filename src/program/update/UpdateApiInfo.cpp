#include "UpdateApiInfo.h"

UpdateApiInfo::UpdateApiInfo(cJSON* json, const cJSON* tagName)
{
    mTagName = tagName->valuestring;

    const cJSON* releaseName = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (cJSON_IsString(releaseName) && releaseName->valuestring)
        mName = releaseName->valuestring;

    const cJSON* authorObj = cJSON_GetObjectItemCaseSensitive(json, "author");
    if (cJSON_IsObject(authorObj)) {
        const cJSON* authorName = cJSON_GetObjectItemCaseSensitive(authorObj, "login");
        if (cJSON_IsString(authorName) && authorName->valuestring)
            mAuthorName = authorName->valuestring;
    }

    const cJSON* date = cJSON_GetObjectItemCaseSensitive(json, "published_at");
    if (cJSON_IsString(date) && date->valuestring)
        mPublishDate = date->valuestring;

    const cJSON* prerelease = cJSON_GetObjectItemCaseSensitive(json, "prerelease");
    if (cJSON_IsBool(prerelease))
        mIsPrerelease = cJSON_IsTrue(prerelease);
}