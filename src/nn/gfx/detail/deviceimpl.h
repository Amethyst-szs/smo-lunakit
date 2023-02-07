/**
 * @file deviceimpl.h
 * @brief Device implementation for GFX.
 */

#pragma once

#include "../../../nvn/nvn.h"
#include "../device.h"

namespace nn
{
    namespace gfx
    {
        namespace detail
        {
            template<typename T>
            class DeviceImpl
            {
            public:
                DeviceImpl();
                ~DeviceImpl();

                void Initialize(nn::gfx::DeviceInfo const &deviceInfo);
                void Finalize();

                NVNdevice *mDevice;
            };
        };
    };
};