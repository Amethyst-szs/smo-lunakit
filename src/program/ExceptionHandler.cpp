#include "logger/Logger.hpp"
#include <cstdio>
#include <cxxabi.h>
#include <lib.hpp>
#include <program/ExceptionHandler.h>
#include <thread/seadThread.h>
#include <thread/seadThreadLocalStorage.h>
#include <utility>

namespace handler {
    char handlerStack[0x20000] = {};
    CatchFunc handlerFunc = nullptr;
    ExceptionInfo exceptionInfo = {};

    namespace detail {
        namespace local {
            struct CatchStackFrame {
                static constexpr int registerCount = 10;
                static constexpr int startingRegister = 19;
                uintptr_t savedRegisters[registerCount] = {};
                uintptr_t sp = 0;
                stack_frame* fp = nullptr;
                uintptr_t lr = 0;
                uintptr_t pc = 0;
                const CatchFunc& catchFunc;
                CatchStackFrame* parentFrame = nullptr;

                explicit CatchStackFrame(const CatchFunc& func) : catchFunc(func) {}
            };

            static sead::ThreadLocalStorage catchStackBottom = sead::ThreadLocalStorage();

            NOINLINE void popCatch() {
                auto* frame = reinterpret_cast<CatchStackFrame*>(catchStackBottom.getValue());
                EXL_ASSERT(frame != nullptr, "Current catch stack frame is null!");
                catchStackBottom.setValue(reinterpret_cast<uintptr_t>(frame->parentFrame));
                free(frame);
            }

            NOINLINE CatchStackFrame* pushCatch(const CatchFunc& func, uintptr_t sp, uintptr_t fp) {
                auto* previousFrame = reinterpret_cast<CatchStackFrame*>(catchStackBottom.getValue());
                auto* newFrame = reinterpret_cast<CatchStackFrame*>(malloc(sizeof(CatchStackFrame)));
                new (newFrame) CatchStackFrame(func);
                newFrame->parentFrame = previousFrame;
                newFrame->pc = reinterpret_cast<uintptr_t>(&popCatch);
                newFrame->sp = sp;
                newFrame->fp = reinterpret_cast<stack_frame*>(fp);
                catchStackBottom.setValue(reinterpret_cast<uintptr_t>(newFrame));
                return newFrame;
            }

            enum class CatchAction : u32 { Skip, Continue, Exit };

            static CatchAction tryCallCatch(ExceptionInfo& info) {
                auto* frame = reinterpret_cast<CatchStackFrame*>(catchStackBottom.getValue());
                if (!frame)
                    return CatchAction::Skip;
                ExceptionInfo tempInfo = info;
                if (!frame->catchFunc || frame->catchFunc(tempInfo)) {
                    info.sp = frame->sp;
                    info.fp = reinterpret_cast<uintptr_t>(frame->fp);
                    info.lr = frame->lr;
                    info.pc = frame->pc;
                    std::copy(std::begin(frame->savedRegisters), std::end(frame->savedRegisters),
                              std::next(std::begin(frame->savedRegisters), CatchStackFrame::startingRegister));
                    return CatchAction::Continue;
                } else
                    return CatchAction::Exit;
            }

        } // namespace local

        static char* getFileNameFromPath(char* path) {
            if (path == nullptr)
                return nullptr;

            char* pFileName = path;
            for (char* pCur = path; *pCur != '\0'; pCur++) {
                if (*pCur == '/' || *pCur == '\\')
                    pFileName = pCur + 1;
            }

            return pFileName;
        }

        static bool isIllegalSymbolAddress(ulong sym, ulong addr) {
            return sym == 0 || (addr - sym) > nn::diag::GetSymbolSize(sym);
        }

        static bool findContainModule(nn::diag::ModuleInfo& result, nn::diag::ModuleInfo* moduleInfos, int moduleCount,
                                      uintptr_t addr) {
            for (int i = 0; i < moduleCount; ++i) {
                nn::diag::ModuleInfo& info = moduleInfos[i];

                uintptr_t moduleStart = info.mBaseAddr;
                uintptr_t moduleEnd = info.mBaseAddr + info.mSize;

                if (addr >= moduleStart && addr <= moduleEnd) {
                    result = moduleInfos[i];
                    return true;
                }
            }
            return false;
        }

        static const char* demangle(const char* symbol) {
            int status = 0;
            return abi::__cxa_demangle(symbol, nullptr, nullptr, &status);
        }

        static void printTraceEntry(const char* traceName, ulong addr, nn::diag::ModuleInfo* moduleInfos,
                                    int moduleCount) {
            nn::diag::ModuleInfo containInfo = {};

            char symbol[0x100] = {};
            uintptr_t symAddr;
            if (addr != 0)
                symAddr = nn::diag::GetSymbolName(symbol, 0x100, addr);
            else
                symAddr = 0;

            if (isIllegalSymbolAddress(symAddr, addr)) {

                if (findContainModule(containInfo, moduleInfos, moduleCount, addr)) {
                    Logger::log("  %s: 0x%p (%s + 0x%zx)\n", traceName, addr,
                                getFileNameFromPath(containInfo.mPath), addr - containInfo.mBaseAddr);
                } else {
                    Logger::log("  %s: 0x%p\n", traceName, addr);
                }
            } else {
                findContainModule(containInfo, moduleInfos, moduleCount, addr);

                const char* demangledName = demangle(symbol);
                if (demangledName) {
                    Logger::log("  %s: 0x%p (%s + 0x%zx)\n    - %s + 0x%zx\n    - %s\n", traceName, addr, getFileNameFromPath(containInfo.mPath), addr - containInfo.mBaseAddr,
                                symbol, addr - symAddr, demangledName);
                    std::free((void*)demangledName);
                } else
                    Logger::log("  %s: 0x%p (%s + 0x%zx)\n    - %s + 0x%zx\n", traceName, addr, getFileNameFromPath(containInfo.mPath), addr - containInfo.mBaseAddr,
                                symbol, addr - symAddr);
            }
        }

        static void printRegister(uintptr_t addr, nn::diag::ModuleInfo* moduleInfos, int moduleCount) {
            nn::diag::ModuleInfo containInfo = {};

            char symbol[0x200] = {};
            uintptr_t symAddr;
            if (addr != 0)
                symAddr = nn::diag::GetSymbolName(symbol, 0x200, addr);
            else
                symAddr = 0;

            if (isIllegalSymbolAddress(symAddr, addr)) {
                if (findContainModule(containInfo, moduleInfos, moduleCount, addr)) {
                    Logger::log(" (unknown) (%s + 0x%zx)\n", getFileNameFromPath(containInfo.mPath),
                                addr - containInfo.mBaseAddr);
                } else {
                    Logger::log("\n");
                }
            } else {
                findContainModule(containInfo, moduleInfos, moduleCount, addr);
                const char* demangledName = demangle(symbol);
                if (demangledName) {
                    Logger::log(" (%s + 0x%zx) (%s + 0x%zx) - %s\n", getFileNameFromPath(containInfo.mPath), addr - symAddr,
                                symbol, addr - containInfo.mBaseAddr, demangledName);
                    std::free((void*)demangledName);
                } else
                    Logger::log(" (%s + 0x%zx) (%s + 0x%zx)\n", getFileNameFromPath(containInfo.mPath), addr - symAddr,
                                symbol, addr - containInfo.mBaseAddr);
            }
        }

        static void printReason(ExceptionType type) {
            Logger::log("Type: ");

            switch (type) {
            case ExceptionType::Init:
                Logger::log("Init\n");
                break;
            case ExceptionType::InstructionAbort:
                Logger::log("InstructionAbort\n");
                break;
            case ExceptionType::DataAbort:
                Logger::log("DataAbort\n");
                break;
            case ExceptionType::UnalignedInstruction:
                Logger::log("UnalignedInstruction\n");
                break;
            case ExceptionType::UnalignedData:
                Logger::log("UnalignedData\n");
                break;
            case ExceptionType::UndefinedInstruction:
                Logger::log("UndefinedInstruction\n");
                break;
            case ExceptionType::ExceptionInstruction:
                Logger::log("ExceptionInstruction\n");
                break;
            case ExceptionType::MemorySystemError:
                Logger::log("MemorySystemError\n");
                break;
            case ExceptionType::FpuException:
                Logger::log("FpuException\n");
                break;
            case ExceptionType::InvalidSystemCall:
                Logger::log("InvalidSystemCall\n");
                break;
            case ExceptionType::SystemCallBreak:
                Logger::log("SystemCallBreak\n");
                break;
            case ExceptionType::AtmosphereStdAbort:
                Logger::log("AtmosphereStdAbort\n");
                break;
            default:
                Logger::log("Unknown!\n");
                break;
            }
        }

        static void printCrashReport(const ExceptionInfo* info) {
            Logger::log("Exception Caught! Core: %u\n", nn::os::GetCurrentCoreNumber());
            printReason(info->type);
            Logger::log("ESR     = %08x 0b", info->esr);
            for (int i = 31; i >= 0; i--) {
                Logger::log((info->esr & BIT(i)) != 0 ? "1" : "0");
            }
            Logger::log("\n");

            // Module Data (used for module dump and stack trace offsets)

            nn::diag::ModuleInfo* moduleInfos;
            uintptr_t bufSize = nn::diag::GetRequiredBufferSizeForGetAllModuleInfo();
            void* moduleBuffer = alloca(bufSize);

            int moduleCount = nn::diag::GetAllModuleInfo(&moduleInfos, moduleBuffer, bufSize);

            Logger::log("FAR     = 0x%016llX (%21lld)", info->far, info->far);
            printRegister(info->far, moduleInfos, moduleCount);

            // Register Dump

            for (int i = 0; i < ACNT(info->r); ++i) {
                Logger::log("r%-2d     = 0x%016llX (%21lld)", i, info->r[i], info->r[i]);
                printRegister(info->r[i], moduleInfos, moduleCount);
            }

            Logger::log("FP      = 0x%016llX (%21lld)\n", info->fp, info->fp);
            Logger::log("LR      = 0x%016llX (%21lld)", info->lr, info->lr);
            printRegister(info->lr, moduleInfos, moduleCount);
            Logger::log("SP      = 0x%016llX (%21lld)\n", info->sp, info->sp);
            Logger::log("PC      = 0x%016llX (%21lld)", info->pc, info->pc);
            printRegister(info->pc, moduleInfos, moduleCount);
            Logger::log("\n");

            // Stack Trace

            Logger::log("Stack trace:\n");

            printTraceEntry("PC", info->pc, moduleInfos, moduleCount);
            printTraceEntry("LR", info->lr, moduleInfos, moduleCount);

            auto frame = (stack_frame*)info->fp;
            stack_frame* prevFrame = nullptr;
            int index = 0;
            while (frame != nullptr && frame != prevFrame) {
                MemoryInfo memInfo;
                u32 pageInfo;
                if (R_FAILED(svcQueryMemory(&memInfo, &pageInfo, (uintptr_t)frame)) || (memInfo.perm & Perm_R) == 0)
                    break;
                prevFrame = frame;

                if (index != 0) {
                    char traceName[0x20] = {};
                    sprintf(traceName, "ReturnAddress[%d]", index);

                    printTraceEntry(traceName, frame->lr, moduleInfos, moduleCount);
                }
                index++;

                frame = frame->fp;
            }

            // Modules

            Logger::log("Module Info:\n");
            Logger::log("Number of Modules: %d\n", moduleCount);
            Logger::log("  %-*s   %-*s   path\n", 16, "base", 16, "size");

            for (int i = 0; i < moduleCount; ++i) {
                nn::diag::ModuleInfo& curInfo = moduleInfos[i];
                Logger::log("  0x%P 0x%P %s\n", curInfo.mBaseAddr, curInfo.mSize, getFileNameFromPath(curInfo.mPath));
            }
        }

        // Implemented in assembly
        [[noreturn]] extern void phaseFourHandler(ExceptionInfo* info);

        void phaseThreeHandler(ExceptionInfo* info) {
            local::CatchAction action = local::tryCallCatch(*info);
            if (action != local::CatchAction::Skip) {
                info->exceptionState =
                    action == local::CatchAction::Continue ? ExceptionState::Continue : ExceptionState::Exit;
            } else {
                bool continueRunning = false;
                if (handlerFunc)
                    continueRunning = handlerFunc(*info);
                else
                    printCrashReport(info);

                info->exceptionState = continueRunning ? ExceptionState::Continue : ExceptionState::Exit;
            }
            phaseFourHandler(info);
        }

        struct KernelExceptionInfo {
            uintptr_t r[9];
            uintptr_t lr;
            uintptr_t sp;
            uintptr_t pc;
            u32 pstate;
            u32 afsr0;
            u32 afsr1;
            u32 esr;
            uintptr_t far;
        };

        // Implemented in assembly
        extern void phaseTwoHandler(int registers[9]);

        static void phaseOneHandler(ExceptionType exceptionType, KernelExceptionInfo& info) {
            if (exceptionType == ExceptionType::InvalidSystemCall && (info.esr & 0xFFFF) == 0xBEEF) {
                // Caused by phase four, we should just jump to the restore and return
                for (int i = 0; i < ACNT(info.r); i++) {
                    info.r[i] = exceptionInfo.r[i];
                }
                info.lr = exceptionInfo.lr;
                info.sp = exceptionInfo.sp;
                info.pc = exceptionInfo.pc;
                info.pstate = exceptionInfo.pstate;
                info.afsr0 = exceptionInfo.afsr0;
                info.afsr1 = exceptionInfo.afsr1;
                info.esr = exceptionInfo.esr;
                info.far = exceptionInfo.far;
                auto state = exceptionInfo.exceptionState;
                exceptionInfo.exceptionState = ExceptionState::FirstChance;
                svcReturnFromException(state == ExceptionState::Exit);
            }

            if (exceptionInfo.exceptionState == ExceptionState::SecondChance)
                svcReturnFromException(1);
            exceptionInfo.exceptionState = ExceptionState::SecondChance;
            for (int i = 0; i < ACNT(info.r); i++) {
                exceptionInfo.r[i] = info.r[i];
            }
            exceptionInfo.lr = info.lr;
            exceptionInfo.sp = info.sp;
            exceptionInfo.pc = info.pc;
            exceptionInfo.pstate = info.pstate;
            exceptionInfo.afsr0 = info.afsr0;
            exceptionInfo.afsr1 = info.afsr1;
            exceptionInfo.esr = info.esr;
            exceptionInfo.far = info.far;
            exceptionInfo.type = exceptionType;
            info.pc = reinterpret_cast<uintptr_t>(phaseTwoHandler);
            info.sp = reinterpret_cast<uintptr_t>(std::end(handlerStack));
            info.r[0] = reinterpret_cast<uintptr_t>(&exceptionInfo);
            svcReturnFromException(exl::result::Success);
        }
    } // namespace detail

    void printCrashReport(const ExceptionInfo& info) { detail::printCrashReport(&info); }

    void installExceptionHandler(const CatchFunc& handler) {
        handlerFunc = handler;
        {
            exl::util::RwPages patcher(exl::util::GetRtldModuleInfo().m_Text.m_Start + 0xb0, 0x4);
            u32* branchPtr = reinterpret_cast<u32*>(patcher.GetRw());
            *branchPtr = exl::armv8::inst::Branch(0x1c).Value();
        }
        auto& handlerFunctionOffset = *(uintptr_t*)(exl::util::GetRtldModuleInfo().m_Data.m_Start + 0x1d0);
        handlerFunctionOffset = reinterpret_cast<uintptr_t>(detail::phaseOneHandler);
    }

} // namespace handler