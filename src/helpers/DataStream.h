#pragma once

#include "types.h"
#include "heap/seadHeapMgr.h"
#include "logger/Logger.hpp"
#include "helpers.h"

class DataStream {
    u8* mBuffer = nullptr;
    u32 mBufferMaxSize = 0;
    u32 mBufferPos = 0;
    sead::Heap* mHeap = nullptr;

    /// resizes the buffer by the amount specified.
    /// \param amt size to add to the buffer (not the new size of the buffer).
    /// \return True if reallocation was successful.
    /// \return False if heap cannot support new size, or reallocation fails.
    bool resize(u32 amt) {
        u32 newSize = mBufferMaxSize + (amt - (mBufferMaxSize - mBufferPos));
        if(mHeap->getFreeSize() > newSize) {
            // note: if reallocation fails, the game crashes
            u8* newBuffer = (u8*)mHeap->tryRealloc(mBuffer, newSize, sizeof(u8*));
            if(!newBuffer)
                return false;
            mBuffer = newBuffer;
            mBufferMaxSize = newSize;
            return true;
        }
        return false;
    }
public:
    explicit DataStream(u32 startSize) {
        if(startSize > 0) {
            mBuffer = new u8[startSize]();
            mBufferMaxSize = startSize;
        }
        mBufferPos = 0;
        mHeap = sead::HeapMgr::instance()->getCurrentHeap();
    }

    ~DataStream() {
        Logger::log("Cleaning up Stream.\n");
        delete mBuffer;
    }

    template <typename T>
    u32 write(T* data, u32 len = sizeof(T)) {
        if(mBufferPos + len > mBufferMaxSize) {
            if(!resize(len))
                return 0;
        }
        memcpy(mBuffer + mBufferPos, data, len);
        mBufferPos += len;
        return len;
    }

    template <typename T>
    u32 read(T* data, u32 len = sizeof(T)) {
        u32 readSize = mBufferPos + len > mBufferMaxSize ? len : mBufferMaxSize - mBufferPos;
        memcpy(data, mBuffer + mBufferPos, readSize);
        mBufferPos += readSize;
        return readSize;
    }

    void rewind(u32 len = 0) {
        if(len == 0)
            mBufferPos = 0;
        else {
            mBufferPos -= len;
            if(mBufferPos < 0)
                mBufferPos = 0;
        }
    }

    void skip(u32 len) {
        if(mBufferPos + len > mBufferMaxSize) {
            if(!resize(len))
                return;
        }
        memset(mBuffer + mBufferPos, 0, len);
        mBufferPos += len;
    }

    // TODO: change this to the current size, not the max size
    u32 getSize() const {
        return mBufferMaxSize;
    }

    u8* getData() const {
        return mBuffer;
    }

    bool isAtEnd() const {
        return mBufferPos == mBufferMaxSize;
    }



};