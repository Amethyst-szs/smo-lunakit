#pragma once

#include "Library/Yaml/ByamlIter.h"
#include "Library/Yaml/Writer/ByamlWriter.h"

#include "nn/types.h"
#include "sead/heap/seadDisposer.h"
#include "vapours/results.hpp"

#include "helpers/fsHelper.h"

#include "devgui/savedata/DevGuiWriteStream.h"

#define LOGGERSAVEPATH "sd:/LunaKit/LKData/logger.byml"

enum class LoggerState {
    UNINITIALIZED = 0,
    CONNECTED = 1,
    UNAVAILABLE = 2,
    DISCONNECTED = 3
};

class Logger {
public:
    Logger() = default;

    static Logger &instance();

    s32 init(sead::Heap* heap);

    static void log(const char *fmt, ...);
    static void log(const char *fmt, va_list args);

    s32 writeLoggerSave(sead::Heap* heap, bool disable, const char* ip, u32 port);

    static bool getDisabledState() { return instance().mIsDisabled; }

private:
    LoggerState mState;
    int mSocketFd;
    bool mIsDisabled;

    sead::RamStreamSrc* mRamStream;
    DevGuiWriteStream* mWriteStream;
    u8 mWorkBuf[0x100];
};
