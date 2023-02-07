#include "MemoryBuffer.h"
#include "imgui_impl_nvn.hpp"

MemoryBuffer::MemoryBuffer(size_t size) {

    auto *bd = ImguiNvnBackend::getBackendData();

    size_t alignedSize = ALIGN_UP(size, 0x1000);

    memBuffer = IM_ALLOC(alignedSize);
    memset(memBuffer, 0, alignedSize);

    bd->memPoolBuilder.SetDefaults()
            .SetDevice(bd->device)
            .SetFlags(nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED)
            .SetStorage(memBuffer, alignedSize);

    if (!pool.Initialize(&bd->memPoolBuilder)) {
        return;
    }

    bd->bufferBuilder.SetDevice(bd->device).SetDefaults().SetStorage(&pool, 0, alignedSize);

    if (!buffer.Initialize(&bd->bufferBuilder)) {
        return;
    }

    mIsReady = true;
}

MemoryBuffer::MemoryBuffer(size_t size, nvn::MemoryPoolFlags flags) {

    auto *bd = ImguiNvnBackend::getBackendData();

    size_t alignedSize = ALIGN_UP(size, 0x1000);

    memBuffer = IM_ALLOC(alignedSize);
    memset(memBuffer, 0, alignedSize);

    bd->memPoolBuilder.SetDefaults()
            .SetDevice(bd->device)
            .SetFlags(flags)
            .SetStorage(memBuffer, alignedSize);

    if (!pool.Initialize(&bd->memPoolBuilder)) {
        return;
    }

    bd->bufferBuilder.SetDevice(bd->device).SetDefaults().SetStorage(&pool, 0, alignedSize);

    if (!buffer.Initialize(&bd->bufferBuilder)) {
        return;
    }

    mIsReady = true;
}

MemoryBuffer::MemoryBuffer(size_t size, void *bufferPtr, nvn::MemoryPoolFlags flags) {

    auto *bd = ImguiNvnBackend::getBackendData();

    memBuffer = bufferPtr;

    bd->memPoolBuilder.SetDefaults()
            .SetDevice(bd->device)
            .SetFlags(flags)
            .SetStorage(memBuffer, size);

    if (!pool.Initialize(&bd->memPoolBuilder)) {
        return;
    }

    bd->bufferBuilder.SetDevice(bd->device).SetDefaults().SetStorage(&pool, 0, size);

    if (!buffer.Initialize(&bd->bufferBuilder)) {
        return;
    }

    mIsReady = true;
}

void MemoryBuffer::Finalize() {
    IM_FREE(memBuffer);
    pool.Finalize();
    buffer.Finalize();
}

void MemoryBuffer::ClearBuffer() {
    memset(memBuffer, 0, pool.GetSize());
}