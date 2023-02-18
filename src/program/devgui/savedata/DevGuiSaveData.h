#pragma once

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

class DevGuiSaveData {
public:
    DevGuiSaveData() {};
    void init();

    void read();
    void write();

    void writeTestFile();

private:
    DevGuiManager* mParent = nullptr;

    u8 mWorkBuf[0x400] = {};
};