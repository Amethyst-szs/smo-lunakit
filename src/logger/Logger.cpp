#include "Logger.hpp"
#include "socket.h"
#include "socket.hpp"
#include "nifm.h"
#include "util.h"
#include "lib.hpp"

char socketPool[0x600000 + 0x20000] __attribute__((aligned(0x1000)));

Logger &Logger::instance() {
    static Logger instance = {};
    return instance;
}

nn::Result Logger::init(sead::Heap* heap) {
    if (mState != LoggerState::UNINITIALIZED)
        return -1;

    sead::Stream::Modes streamMode = sead::Stream::Modes::Binary;
    mRamStream = new sead::RamStreamSrc(&mWorkBuf, sizeof(mWorkBuf));
    mWriteStream = new DevGuiWriteStream(mRamStream, streamMode);

    if(!FsHelper::isFileExist(LOGGERSAVEPATH)) {
        writeLoggerSave(heap, true, "0", 0);
        mIsDisabled = true;
        mState = LoggerState::CONNECTED;
        return 0;
    }

    FsHelper::LoadData loadData = {
        .path = LOGGERSAVEPATH
    };

    FsHelper::loadFileFromPath(loadData);
    al::ByamlIter root = al::ByamlIter((u8*)loadData.buffer);

    root.tryGetBoolByKey(&mIsDisabled, "Disable");

    if (mIsDisabled) {
        mState = LoggerState::CONNECTED;
        return 0;
    }

    in_addr hostAddress = {0};
    sockaddr serverAddress = {0};

    const char* ip = nullptr;
    u32 port;

    root.tryGetStringByKey(&ip, "IP");
    root.tryGetUIntByKey(&port, "Port");

    nn::nifm::Initialize();

    /*s32 initResult = */nn::socket::Initialize(socketPool, 0x600000, 0x20000, 0xE);

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

    if (instance().mState != LoggerState::CONNECTED && !instance().mIsDisabled)
        return;

    va_list args;
    va_start(args, fmt);

    char buffer[0x500] = {};

    if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {
        if (instance().mIsDisabled) {
            svcOutputDebugString(buffer, strlen(buffer));
        } else {
            char prefix[0x510];
            nn::util::SNPrintf(prefix, sizeof(prefix), "%s", buffer);
            nn::socket::Send(instance().mSocketFd, prefix, strlen(prefix), 0);
        }
    }

    va_end(args);
}

void Logger::log(const char *fmt, va_list args) {

    if (instance().mState != LoggerState::CONNECTED)
        return;

    char buffer[0x500] = {};

    if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {
        char prefix[0x510];
        nn::util::SNPrintf(prefix, sizeof(prefix), "%s", buffer);
        nn::socket::Send(instance().mSocketFd, prefix, strlen(prefix), 0);
    }
}

nn::Result Logger::writeLoggerSave(sead::Heap* heap, bool disable, const char* ip, uint port) {
    if(disable && !mIsDisabled)
        Logger::log("Logger disabled! Goodbye!\n");
    
    mWriteStream->rewind();
    al::ByamlWriter file = al::ByamlWriter(heap, false);
    
    file.pushHash();

    file.addBool("Disable", disable);
    file.addString("IP", ip);
    file.addUInt("Port", port);

    file.pop();
    file.write(mWriteStream);

    nn::Result result = FsHelper::writeFileToPath(mWorkBuf, file.calcPackSize(), LOGGERSAVEPATH);

    return result;
}