#include "LoadLogger.hpp"
#include "devgui/DevGuiManager.h"
#include "lib.hpp"
#include "nifm.h"
#include "util.h"

void LoadLog::pushTextToVector(const char* text) {
    sead::DateTime currentTime = sead::DateTime(0);
    sead::CalendarTime calendarTime;
    char temp[256];

    currentTime.setNow();
    currentTime.getCalendarTime(&calendarTime);

    if (mTextLines.size() > mMaxListSize)
        mTextLines.erase(mTextLines.begin());
    snprintf(temp, sizeof(temp), "%02d:%02d:%02d | %s", calendarTime.getHour(), calendarTime.getMinute(), calendarTime.getSecond(), text);
    
    mTextLines.push_back(strdup(temp));
}
