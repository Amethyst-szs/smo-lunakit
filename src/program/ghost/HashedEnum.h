#pragma once

#include "crc32.h"
#include "types.h"

#define STRVALUE(value) #value ,

#define HASHED_ENUM(Name, ...) namespace Name {                                    \
    enum Enum : s16 {                                                              \
        Unknown = -1,                                                              \
        __VA_ARGS__ __VA_OPT__(,)                                                  \
        End                                                                        \
    };                                                                             \
    static constexpr u16 ToValue(Enum type) { return static_cast<u16>(type); }     \
    static constexpr Enum ToEnum(u16 value) {return static_cast<Enum>(value);}     \
    static constexpr std::array<const char*, static_cast<u16>(Enum::End)> s_Strs { \
        FOR_EACH(STRVALUE, __VA_ARGS__)                                            \
    };                                                                             \
    static constexpr crc32::HashArray s_Hashes(s_Strs);                            \
    static constexpr Enum FindType(std::string_view const& str) {                  \
        return ToEnum(s_Hashes.FindIndex(str));                                    \
    }                                                                              \
    static constexpr const char *FindStr(Enum type) {                              \
        const u16 type_ = (s16)type;                                               \
        if (0 <= type_ && type_ < s_Strs.size())                                   \
            return s_Strs[type_];                                                  \
        else                                                                       \
            return "";                                                             \
    }                                                                              \
};
