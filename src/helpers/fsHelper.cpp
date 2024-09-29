#include "fsHelper.h"
#include "diag/assert.hpp"
#include "nn/init.h"
#include "nn/fs/fs_directories.h"
#include "nn/fs/fs_files.h"
#include "nn/fs/fs_mount.h"
#include "nn/fs/fs_types.h"
#include "logger/Logger.hpp"
#include "vapours/results.hpp"

namespace FsHelper {
    nn::Result writeFileToPath(void *buf, size_t size, const char *path) {
        nn::fs::FileHandle handle;

        if (isFileExist(path)) {
            nn::fs::DeleteFile(path); // remove previous file
        }

        nn::Result r = nn::fs::CreateFile(path, size);
        if (r.IsFailure()) {
            return r;
        }

        r = nn::fs::OpenFile(&handle, path, nn::fs::OpenMode_Write);
        if (r.IsFailure()) {
            return r;
        }

        r = nn::fs::WriteFile(handle, 0, buf, size, nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush));
        if (r.IsFailure()) {
            return r;
        }

        nn::fs::CloseFile(handle);

        return nn::ResultSuccess{};
    }

    nn::Result appendFileOnPath(void* buf, s64 pos, size_t size, const char* path) {
        nn::fs::FileHandle handle = {};
        nn::Result r;
        if (!isFileExist(path)) {
            r = nn::fs::CreateFile(path, size);
            if (r.IsFailure())
                return r;
        }
        r = nn::fs::OpenFile(&handle, path, nn::fs::OpenMode_Append);
        if (r.IsFailure()) {
            return r;
        }
        r = nn::fs::WriteFile(handle, pos, buf, size, nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush));
        if (r.IsFailure()) {
            return r;
        }
        nn::fs::CloseFile(handle);
        return nn::ResultSuccess{};
    }

    // make sure to free buffer after usage is done
    void loadFileFromPath(LoadData &loadData) {

        nn::fs::FileHandle handle;

        EXL_ASSERT(FsHelper::isFileExist(loadData.path), "Failed to Find File!\nPath: %s", loadData.path);

        R_ABORT_UNLESS(nn::fs::OpenFile(&handle, loadData.path, nn::fs::OpenMode_Read).IsFailure())

        long size = 0;
        nn::fs::GetFileSize(&size, handle);
        loadData.buffer = nn::init::GetAllocator()->Allocate(size);
        loadData.bufSize = size;

        EXL_ASSERT(loadData.buffer, "Failed to Allocate Buffer! File Size: %ld", size);

        R_ABORT_UNLESS(nn::fs::ReadFile(handle, 0, loadData.buffer, size).IsFailure())

        nn::fs::CloseFile(handle);
    }


    long getFileSize(const char *path) {
        nn::fs::FileHandle handle;
        long result = -1;

        nn::Result openResult = nn::fs::OpenFile(&handle, path, nn::fs::OpenMode::OpenMode_Read);

        if (openResult.IsSuccess()) {
            nn::fs::GetFileSize(&result, handle);
            nn::fs::CloseFile(handle);
        }

        return result;
    }

    bool isFileExist(const char *path) {
        nn::fs::DirectoryEntryType type;
        nn::fs::GetEntryType(&type, path);

        return type == nn::fs::DirectoryEntryType_File;
    }
}
