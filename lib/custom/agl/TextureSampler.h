#pragma once

#include "agl/common/aglTextureData.h"
#include <prim/seadSafeString.h>

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
