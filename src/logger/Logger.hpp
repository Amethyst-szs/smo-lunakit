#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/byaml/writer/ByamlWriter.h"

#include "sead/heap/seadDisposer.h"
#include "nn/result.h"

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

    nn::Result init(sead::Heap* heap);

    static void log(const char *fmt, ...);
    static void log(const char *fmt, va_list args);

    nn::Result writeLoggerSave(sead::Heap* heap, bool disable, const char* ip, uint port);

    static bool getDisabledState() { return instance().mIsDisabled; }

private:
    LoggerState mState;
    int mSocketFd;
    bool mIsDisabled;

    sead::RamStreamSrc* mRamStream;
    DevGuiWriteStream* mWriteStream;
    u8 mWorkBuf[0x100];
};