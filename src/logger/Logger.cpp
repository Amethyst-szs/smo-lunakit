#include "Logger.hpp"
#include "socket.h"
#include "nifm.h"
#include "util.h"
#include "lib.hpp"

#define ISEMU false

char socketPool[0x600000 + 0x20000] __attribute__((aligned(0x1000)));

Logger &Logger::instance() {
    static Logger instance = {};
    return instance;
}

nn::Result Logger::init(const char *ip, u16 port) {
    in_addr hostAddress = {0};
    sockaddr serverAddress = {0};

    if (mState != LoggerState::UNINITIALIZED)
        return -1;

    mIsEmulator = ISEMU;

    if (mIsEmulator) {
        mState = LoggerState::CONNECTED;
        return 0;
    }

    nn::nifm::Initialize();

    nn::socket::Initialize(socketPool, 0x600000, 0x20000, 0xE);

    nn::nifm::SubmitNetworkRequest();

    while (nn::nifm::IsNetworkRequestOnHold()) {}

    if (!nn::nifm::IsNetworkAvailable()) {
        mState = LoggerState::UNAVAILABLE;
        return -1;
    }

    if ((mSocketFd = nn::socket::Socket(2, 1, 0)) < 0) {
        mState = LoggerState::UNAVAILABLE;
        return -1;
    }

    nn::socket::InetAton(ip, &hostAddress);

    serverAddress.address = hostAddress;
    serverAddress.port = nn::socket::InetHtons(port);
    serverAddress.family = 2;

    nn::Result result = nn::socket::Connect(mSocketFd, &serverAddress, sizeof(serverAddress));

    mState = result.isSuccess() ? LoggerState::CONNECTED : LoggerState::DISCONNECTED;

    if (mState == LoggerState::CONNECTED) {
        Logger::log("Connected!\n");
    }

    return result;
}

void Logger::log(const char *fmt, ...) {

    if (instance().mState != LoggerState::CONNECTED && !ISEMU)
        return;

    va_list args;
    va_start(args, fmt);

    char buffer[0x500] = {};

    if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {

        if (ISEMU) {
            svcOutputDebugString(buffer, strlen(buffer));
        } else {
            nn::socket::Send(instance().mSocketFd, buffer, strlen(buffer), 0);
        }
    }

    va_end(args);
}

void Logger::log(const char *fmt, va_list args) {

    if (instance().mState != LoggerState::CONNECTED)
        return;

    char buffer[0x500] = {};

    if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {
        nn::socket::Send(instance().mSocketFd, buffer, strlen(buffer), 0);
    }
}
