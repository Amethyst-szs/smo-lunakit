#pragma once

#include "agl/util.h"
#include "detail/Surface.h"
#include "driver/NVNtexture.h"
#include <prim/seadSafeString.h>
#include "TextureData.h"

namespace agl
{
    class TextureSampler
    {
    public:
        TextureSampler();
        TextureSampler(agl::TextureData const&);
        void applyTextureData(agl::TextureData const&);

        void* unk1;
        agl::TextureData mTextureData;
        char unk2[0x40];
    };
};