#pragma once

#include "types.h"
#include <nn/diag.h>
#include <nn/os.h>

void exception_handler(nn::os::UserExceptionInfo *info);

bool isIllegalSymbolAddress(ulong sym, ulong addr);

bool findContainModule(nn::diag::ModuleInfo *result, nn::diag::ModuleInfo *moduleInfos, int moduleCount, u64 addr);

void printTraceEntry(const char *traceName, ulong addr, nn::diag::ModuleInfo *moduleInfos, int moduleCount);

void installExceptionStub();

struct stack_frame {
    stack_frame* prevFp;
    size_t lr;
};