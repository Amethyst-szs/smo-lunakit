#pragma once

#include "nvn/nvn_Cpp.h"

// simple maker function for constructing a memory pool
namespace MemoryPoolMaker {
    bool createPool(nvn::MemoryPool *result, size_t size,
                    const nvn::MemoryPoolFlags &flags = nvn::MemoryPoolFlags::CPU_UNCACHED |
                                                        nvn::MemoryPoolFlags::GPU_CACHED);
}
