#pragma once

#include "types.h"
#include <functional>
#include <nn/diag.h>
#include <nn/os.h>

namespace handler {

    struct stack_frame {
        stack_frame* fp;
        size_t lr;
    };

    enum class ExceptionType : u32 {
        Init = 0x000,
        InstructionAbort = 0x100,
        DataAbort = 0x101,
        UnalignedInstruction = 0x102,
        UnalignedData = 0x103,
        UndefinedInstruction = 0x104,
        ExceptionInstruction = 0x105,
        MemorySystemError = 0x106,
        FpuException = 0x200,
        InvalidSystemCall = 0x301,
        SystemCallBreak = 0x302,

        AtmosphereStdAbort = 0xFFE,
    };

    enum class ExceptionState : u32 { FirstChance, SecondChance, Continue, Exit };

    struct ExceptionInfo {
        uintptr_t r[29];
        uintptr_t fp;
        uintptr_t lr;
        uintptr_t sp;
        uintptr_t pc;
        u32 pstate;
        u32 afsr0;
        u32 afsr1;
        u32 esr;
        uintptr_t far;
        ExceptionType type;
        ExceptionState exceptionState;
    };

    using TryFunc = std::function<void()>;
    using CatchFunc = std::function<bool(ExceptionInfo& info)>;

    // Implemented in assembly
    void tryCatch(const TryFunc& tryFunc, const CatchFunc& catchFunc);
    void installExceptionHandler(const CatchFunc& handler);
    void printCrashReport(const ExceptionInfo& info);
} // namespace handler