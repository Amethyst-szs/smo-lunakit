#pragma once

#include "NintendoSDK/nn/settings.h"

namespace nn {
namespace settings {
    namespace system {
        struct FirmwareVersion {
            u8 major;
            u8 minor;
            u8 micro;
            u8 padding1;
            u8 revision_major;
            u8 revision_minor;
            u8 padding2;
            u8 padding3;
            char platform[0x20];
            char version_hash[0x40];
            char display_version[0x18];
            char display_title[0x80];

            constexpr inline u32 getVersion() const {
                return (static_cast<u32>(major) << 16) | (static_cast<u32>(minor) << 8) |
                       (static_cast<u32>(micro) << 0);
            }
        };

        Result GetFirmwareVersion(FirmwareVersion*);
    }  // namespace system

};  // namespace settings
};  // namespace nn
