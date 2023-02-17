#pragma once

#include "basis/seadTypes.h"
#include "stream/seadStreamSrc.h"

namespace sead {
class RamStreamSrc : public StreamSrc {
public:
    RamStreamSrc(void *buffer, u32 size);
    ~RamStreamSrc();

    u32 read(void *ptr,u32 size) override;
    u32 write(void const*,u32) override;
    u32 skip(int) override;
    void rewind() override;
    bool isEOF() override;
private:
    void *mSrcBuffer;
    u32 mSrcSize;
    u32 mCursorPos;
};
}