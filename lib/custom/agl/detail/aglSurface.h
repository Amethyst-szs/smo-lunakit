#pragma once

#include <nvn/nvn.h>
#include <basis/seadTypes.h>
#include "common/aglTextureEnum.h"

namespace agl::detail {

struct SurfaceBase;

class Surface {
public:
    Surface();
    void initialize(TextureType, TextureFormat, u32, TextureAttribute, MultiSampleType);
    void initializeSize(u32, u32, u32);
    void copyFrom(const SurfaceBase&);
    void calcSizeAndAlignment();
    void setupNVNtextureBuilder(NVNtextureBuilder*) const;
    void printInfo() const;
    void copyFrom(const NVNtexture&);

    u16 mWidth;
    u16 mHeight;
private:
    u16 _4;
    u16 _6;
    u8 _8;
    u8 _9;
    u16 _a;
    u8 _c[0x1A - 0xC];
    u8 _1a;
    u8 _1b;
    u32 _1c;
    u8 _20;
    u8 _21;
    u8 _22;
    u8 _23;
};

struct SurfaceBase {
    void* _0;
    void* _8;
    void* _10;
};

}  // namespace agl::detail
