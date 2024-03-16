#pragma once

#include "nn/types.h"

namespace FsHelper {

    struct LoadData {
        const char *path;
        void *buffer;
        long bufSize;
    };

    nn::Result writeFileToPath(void *buf, size_t size, const char *path);

    nn::Result appendFileOnPath(void* buf, s64 pos, size_t size, const char* path);

    void loadFileFromPath(LoadData &loadData);

    long getFileSize(const char *path);

    bool isFileExist(const char *path);
}
