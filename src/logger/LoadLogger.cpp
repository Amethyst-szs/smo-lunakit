#include "LoadLogger.hpp"
#include "devgui/DevGuiManager.h"
#include "lib.hpp"
#include "nifm.h"
#include "socket.h"
#include "util.h"

void LoadLog::pushTextToVector(const char* text) {
    sead::DateTime currentTime = sead::DateTime(0);
    sead::CalendarTime calendarTime;
    char temp[256];

    currentTime.setNow();
    currentTime.getCalendarTime(&calendarTime);

    if (mTextLines.size() > 4000) 
        mTextLines.erase(mTextLines.begin());
    snprintf(temp, sizeof(temp), "%02d:%02d:%02d\t|\t%s", calendarTime.getHour(), calendarTime.getMinute(), calendarTime.getSecond(), text);
    
    mTextLines.push_back(strdup(temp));
}
