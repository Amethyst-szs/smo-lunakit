#pragma once

#include "sead/stream/seadRamWriteStream.h"
#include "sead/stream/seadStream.h"

// This class (DevGuiWriteStream) is not the main class! This is a custom implementation of sead::WriteStream
// Which is passed into the al::ByamlWriter to create a buffer which is written to the save file!
class DevGuiWriteStream : public sead::WriteStream {
public:
    DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode)
    {
        mSrc = src;
        setMode(mode);
    }
};