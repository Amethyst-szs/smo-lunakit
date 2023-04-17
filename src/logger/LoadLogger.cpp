#include "LoadLogger.hpp"
#include "devgui/DevGuiManager.h"
#include "lib.hpp"
#include "nifm.h"
#include "util.h"

#include "sead/time/seadDateTime.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(ResourceLoadLogger)
ResourceLoadLogger::ResourceLoadLogger() = default;
ResourceLoadLogger::~ResourceLoadLogger() = default;

void ResourceLoadLogger::init(sead::Heap* heap)
{
    mHeap = heap;
    mTextLines.tryAllocBuffer(mMaxListSize, heap);
}

void ResourceLoadLogger::pushTextToVector(const char* text)
{
    if (mTextLines.size() >= mMaxListSize)
        delete(mTextLines.popBack());
    
    sead::DateTime currentTime = sead::DateTime(0);
    sead::CalendarTime calendarTime;

    currentTime.setNow();
    currentTime.getCalendarTime(&calendarTime);

    sead::SafeString* entry = new (mHeap) sead::FormatFixedSafeString<0x80>("%02d:%02d:%02d: %s", calendarTime.getHour(), calendarTime.getMinute(), calendarTime.getSecond(), text);
    
    mTextLines.pushFront(entry);
}
