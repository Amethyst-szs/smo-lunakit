/**
 * @file mem.h
 * @brief Memory allocation functions.
 */

#pragma once

#include <nn/os.h>
#include "types.h"

namespace nn {
    namespace mem {
        class StandardAllocator {
        public:
            StandardAllocator();

            void Initialize(void *address, u64 size);

            void Finalize();

            void *Reallocate(void *address, u64 newSize);

            void *Allocate(u64 size);

            void Free(void *address);

            u64 GetSizeOf(const void *) const;

            u64 GetTotalFreeSize(void) const;

            void Dump();

            bool mIsInitialized;         // _0
            bool mIsEnabledThreadCache;  // _1
            u16 _2;
            u64 *mAllocAddr;  // _4
        };
    }  // namespace mem
}  // namespace nn
