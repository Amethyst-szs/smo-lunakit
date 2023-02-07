#pragma once

#include "nvn_Cpp.h"
#include "nvn_CppMethods.h"
#include "types.h"

class MemoryBuffer {
public:
    explicit MemoryBuffer(size_t size);

    explicit MemoryBuffer(size_t size, nvn::MemoryPoolFlags flags);

    explicit MemoryBuffer(size_t size, void *buffer, nvn::MemoryPoolFlags flags);

    void Finalize();

    size_t GetPoolSize() const { return pool.GetSize(); }

    nvn::BufferAddress GetBufferAddress() const { return buffer.GetAddress(); };

    u8 *GetMemPtr() const { return (u8 *) pool.Map(); }

    bool IsBufferReady() { return mIsReady; }

    void ClearBuffer();

    operator nvn::BufferAddress() const { return buffer.GetAddress(); }

private:
    nvn::MemoryPool pool;
    nvn::Buffer buffer;

    void *memBuffer;
    bool mIsReady = false;
};