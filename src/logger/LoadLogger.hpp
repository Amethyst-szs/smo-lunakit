#pragma once

#include "sead/container/seadPtrArray.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadDisposer.h"
#include "sead/prim/seadSafeString.h"

#include "nn/result.h"

#include "helpers/fsHelper.h"

#include "imgui.h"

class ResourceLoadLogger {
    // This class is a singleton! It does not have a typical constructor
    // This is class is created in GameSystemInit in main.cpp
    // Access this class from anywhere using DevGuiManager::instance()->...
    SEAD_SINGLETON_DISPOSER(ResourceLoadLogger);
    ResourceLoadLogger();
    ~ResourceLoadLogger();

public:
    void init(sead::Heap* heap);
    void pushTextToVector(const char* text);

    sead::Heap* mHeap = nullptr;
    static const int mMaxListSize = 1000;
    sead::PtrArray<sead::SafeString> mTextLines;
};