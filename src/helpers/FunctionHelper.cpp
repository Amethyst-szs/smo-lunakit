#include <lib.hpp>
#include "FunctionHelper.h"
#include "ro.h"

namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

static constexpr const u32 RetValue = exl::armv8::inst::Ret().Value();

uintptr_t FunctionHelper::findEndOfFunc(const char* symbol) {
    u32* ptr = (u32*)getAddressFromSymbol(symbol);
    // naive implementation, ignores the fact that functions can have multiple returns
    while (*ptr != RetValue) {
        ptr++;
    }
    return (uintptr_t) ptr;
}

ptrdiff_t FunctionHelper::readLdrOffset(const char* symbol) {
    auto ldr = *reinterpret_cast<inst::LdrRegisterImmediate*>(getAddressFromSymbol(symbol));
    auto rnReg = reg::Register(static_cast<reg::RegisterKind>(ldr.GetSize() & 0b01), ldr.GetRn());
    return ldr.GetImm12() * rnReg.Width();

}