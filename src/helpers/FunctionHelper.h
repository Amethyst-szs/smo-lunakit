#pragma once

#include <cstdint>
#include "nn/ro.h"

namespace FunctionHelper {
    static uintptr_t getAddressFromSymbol(const char* symbol) {
        uintptr_t result;
        nn::ro::LookupSymbol(&result, symbol);
        return result;
    }
    uintptr_t findEndOfFunc(const char* symbol);
    ptrdiff_t readLdrOffset(const char* symbol);
};

