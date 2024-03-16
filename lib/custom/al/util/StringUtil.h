#pragma once

#include <sead/prim/seadSafeString.h>
#include "al/string/StringTmp.h"

namespace al {

bool isEqualString(const char16_t*, const char16_t*);
bool isEqualSubString(const char*, const char*);
bool isEqualSubString(const sead::SafeStringBase<char>&, const sead::SafeStringBase<char>&);
bool isStartWithString(const char*, const char*);
bool isEndWithString(const char*, const char*);
bool isEqualString(const char*, const char*) __attribute__((noinline));
bool isEqualString(const sead::SafeString&, const sead::SafeString&);
};  // namespace al