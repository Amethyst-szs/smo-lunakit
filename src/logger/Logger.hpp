#pragma once

#include "sead/heap/seadDisposer.h"
#include "nn/result.h"

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

    nn::Result init(const char *ip, u16 port);

    static void log(const char *fmt, ...);

    static void log(const char *fmt, va_list args);

private:
    LoggerState mState;
    int mSocketFd;
    bool mIsEmulator;
};