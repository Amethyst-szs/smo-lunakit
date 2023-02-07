#pragma once

#include "../types.h"
/**
 * @file util.h
 * @brief Helper functions for OS functionality.
 */

#pragma once

#include <nx/types.h>
#include <type_traits>

namespace nn {
    namespace util {
        struct Unorm8x4 {
            u8 elements[0x4];
        };

        enum CharacterEncodingResult {
            Success, BadLength, InvalidFormat
        };

        CharacterEncodingResult PickOutCharacterFromUtf8String(char *, char const **str);

        CharacterEncodingResult ConvertCharacterUtf8ToUtf32(u32 *dest, char const *src);

        CharacterEncodingResult ConvertStringUtf16NativeToUtf8(char *, s32, u16 const *, s32);

        CharacterEncodingResult ConvertStringUtf8ToUtf16Native(u16 *, s32, char const *, s32);

        class RelocationTable {
        public:
            void Relocate();

            void Unrelocate();

            s32 mMagic;         // _0
            u32 mPosition;      // _4
            s32 mSectionCount;  // _8
        };

        class BinaryFileHeader {
        public:
            bool IsValid(s64 packedSig, s32 majorVer, s32 minorVer, s32 microVer) const;

            bool IsRelocated() const;

            bool IsEndianReverse() const;

            nn::util::RelocationTable *GetRelocationTable();

            s32 mMagic;                // _0
            u32 mSig;                  // _4
            u8 mVerMicro;              // _8
            u8 mVerMinor;              // _9
            u16 mVerMajor;             // _A
            u16 mBOM;                  // _C
            u8 mAlignment;             // _E
            u8 mTargetAddrSize;        // _F
            u32 mFileNameOffset;       // _10
            u16 mFlag;                 // _14
            u16 mFirstBlockOffs;       // _16
            u32 mRelocationTableOffs;  // _18
            u32 mSize;                 // _1C
        };

//        template<s32 size, typename Enum>
//        struct BitFlagSet {
//            using Storage = std::underlying_type_t<Enum>;
//            Storage field: size;
//
//            inline bool isFlagSet(Enum t) const {
//                return (field & static_cast<Storage>(t)) != 0;
//            }
//        };

        template<s32 size, typename T>
        struct BitFlagSet {
            using type = std::conditional_t<size <= 32, u32, u64>;
            static const int storageBits = static_cast<int>(sizeof(type)) * 8;
            static const int storageCount = static_cast<int>((size + storageBits - 1)) / storageBits;
            type field[storageCount];

            inline bool isBitSet(T index) const {
                return (this->field[static_cast<u64>(index) / storageBits] &
                        (static_cast<type>(1) << static_cast<u64>(index) % storageBits)) != 0;
            }
        };

        s32 SNPrintf(char *s, ulong n, const char *format, ...);

        s32 VSNPrintf(char *s, ulong n, const char *format, va_list arg);
    }  // namespace util

    void ReferSymbol(void const *);
}  // namespace nn
