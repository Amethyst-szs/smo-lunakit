#pragma once

#include "al/camera/CameraPoser.h"
#include "al/camera/CameraTicket.h"

namespace al
{
    class CameraPoseUpdater {
        public:
            unsigned char padding_A0[0xA0];
            al::CameraTicket *mTicket; // 0xA0
    };
};