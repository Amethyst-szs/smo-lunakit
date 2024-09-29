#pragma once

#include "agl/common/aglDrawContext.h"
#include "agl/common/aglRenderBuffer.h"

namespace al
{
    class GameDrawInfo {
        public:
            agl::RenderBuffer *mFirstRenderBuffer; // 0x0
            agl::RenderBuffer *mSecondRenderBuffer; // 0x8
            bool unkBool; // 0x10
            agl::DrawContext *mDrawContext; // 0x18
    };
} // namespace al
