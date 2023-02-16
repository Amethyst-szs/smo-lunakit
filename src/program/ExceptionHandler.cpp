#include "logger/Logger.hpp"
#include <cstdio>
#include <hook/replace.hpp>
#include <program/ExceptionHandler.h>
#include <result.hpp>

char* getFileNameFromPath(char* path)
{
    if(path == nullptr)
        return nullptr;

    char* pFileName = path;
    for(char* pCur = path; *pCur != '\0'; pCur++)
    {
        if( *pCur == '/' || *pCur == '\\' )
            pFileName = pCur+1;
    }

    return pFileName;
}

bool isIllegalSymbolAddress(ulong sym, ulong addr) {
    return sym == 0 || (addr - sym) > nn::diag::GetSymbolSize(sym);
}

bool findContainModule(nn::diag::ModuleInfo &result, nn::diag::ModuleInfo *moduleInfos, int moduleCount, u64 addr) {
    for (int i = 0; i < moduleCount; ++i) {
        nn::diag::ModuleInfo &info = moduleInfos[i];

        u64 moduleStart = info.mBaseAddr;
        u64 moduleEnd = info.mBaseAddr + info.mSize;

        if(addr >= moduleStart && addr <= moduleEnd) {
            result = moduleInfos[i];
            return true;
        }
    }
    return false;
}

void printTraceEntry(const char *traceName, ulong addr, nn::diag::ModuleInfo *moduleInfos, int moduleCount) {

    nn::diag::ModuleInfo containInfo = {};

    char symbol[0x100] = {};
    u64 symAddr;
    if(addr != 0)
        symAddr = nn::diag::GetSymbolName(symbol, 0x100, addr);
    else
        symAddr = 0;

    if(isIllegalSymbolAddress(symAddr, addr)) {

        if(findContainModule(containInfo, moduleInfos, moduleCount, addr)) {
            Logger::log("  %s: 0x%p (unknown) (%s + 0x%zx)\n", traceName, addr, getFileNameFromPath(containInfo.mPath), addr - containInfo.mBaseAddr);
        }else {
            Logger::log("  %s: 0x%p (unknown)\n", traceName, addr);
        }
    }
    else {

        findContainModule(containInfo, moduleInfos, moduleCount, addr);

        Logger::log("  %s: 0x%p (%s + 0x%zx) (%s + 0x%zx)\n", traceName, addr, symbol, addr - symAddr,
                    getFileNameFromPath(containInfo.mPath), addr - containInfo.mBaseAddr);

    }
}

void exception_handler(nn::os::UserExceptionInfo *info) {
    Logger::log("Exception Caught! Core: %u\n", nn::os::GetCurrentCoreNumber());
    Logger::log("Type: %u\n", info->ErrorDescription);

    // Module Data (used for module dump and stack trace offsets)

    nn::diag::ModuleInfo *moduleInfos;
    u64 bufSize = nn::diag::GetRequiredBufferSizeForGetAllModuleInfo();
    void *moduleBuffer = malloc(bufSize);

    if(!moduleBuffer) {
        Logger::log("Module Buffer Allocation Failed. Size: %ld\n", bufSize);
    }

    int moduleCount = nn::diag::GetAllModuleInfo(&moduleInfos, moduleBuffer, bufSize);

    // Register Dump

    for (int i = 2; i != 32; ++i)
        Logger::log("r%-2d     = 0x%016llX (%21lld)\n", i-2, info->CpuRegisters[i].x, info->CpuRegisters[i].x);

    Logger::log("LR      = 0x%016llX (%21lld)\n", info->LR.x, info->LR.x);
    Logger::log("SP      = 0x%016llX (%21lld)\n", info->SP.x, info->SP.x);
    Logger::log("PC      = 0x%016llX (%21lld)\n", info->PC.x, info->PC.x);
    Logger::log("\n");

    // Stack Trace

    Logger::log("Stack trace:\n");

    printTraceEntry("PC", info->PC.x, moduleInfos, moduleCount);
    printTraceEntry("LR", info->LR.x, moduleInfos, moduleCount);

    auto frame = (stack_frame*)info->FP.x;
    stack_frame* prevFrame = nullptr;
    int index = 0;
    while(frame != nullptr && frame != prevFrame) {
        prevFrame = frame;

        char traceName[0x20] = {};
        sprintf(traceName, "ReturnAddress[%d]", index++);

        printTraceEntry(traceName, frame->lr, moduleInfos, moduleCount);
        frame = frame->prevFp;
    }

    // Modules

    Logger::log("Module Info:\n");
    Logger::log("Number of Modules: %d\n", moduleCount);
    Logger::log("  %-*s   %-*s   path\n", 16, "base", 16, "size");

    for (int i = 0; i < moduleCount; ++i) {
        nn::diag::ModuleInfo &curInfo = moduleInfos[i];
        Logger::log("  0x%P 0x%P %s\n", curInfo.mBaseAddr, curInfo.mSize, getFileNameFromPath(curInfo.mPath));
    }

    Logger::log("\n");
}

HOOK_DEFINE_REPLACE(ExceptionHandlerStub) {
    static void Callback() {}
};

void installExceptionStub() {
    ExceptionHandlerStub::InstallAtSymbol("_ZN2nn2os23SetUserExceptionHandlerEPFvPNS0_17UserExceptionInfoEEPvmS2_");
}