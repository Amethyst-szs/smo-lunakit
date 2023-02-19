#pragma once

#include "al/util.hpp"
#include "al/byaml/ByamlIter.h"
#include "al/byaml/writer/ByamlWriter.h"

#include "helpers/fsHelper.h"

#include "nn/fs/fs_directories.hpp"
#include "nn/fs/fs_files.hpp"
#include "nn/fs/fs_types.hpp"

#include "sead/stream/seadRamWriteStream.h"
#include "sead/stream/seadStream.h"

#include "types.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiWriteStream : public sead::WriteStream {
public:
    DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode);
};

class DevGuiSaveData {
public:
    DevGuiSaveData(sead::Heap* heap) { mHeap = heap; };
    void init();

    void read();
    void write();

    void writeTestFile();

private:
    sead::Heap* mHeap = nullptr;
    DevGuiManager* mParent = nullptr;

    sead::RamStreamSrc* mRamStream = nullptr;
    DevGuiWriteStream* mWriteStream = nullptr;
    u8 mWorkBuf[0x400] = {};
};