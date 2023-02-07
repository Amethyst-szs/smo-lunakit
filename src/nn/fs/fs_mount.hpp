#pragma once

#include "fs_types.hpp"

namespace nn::fs {

    /*
        Mount SD card. Must have explicit permission.
        mount: drive to mount to.
    */
    bool MountSdCardForDebug(char const* mount);
};