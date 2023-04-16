#pragma once

#include "agl/TextureData.h"
#include "agl/RenderTargetDepth.h"
#include "al/actor/ActorSceneInfo.h"

namespace agl {
    class SamplerLocation;
}

namespace al {

    class GBufferArray {
        public:
        agl::TextureData *mGBufLightBuffer;
        char gap_8[1120];
        agl::TextureData * mGBufNrmWorld;
        char gap_470[1120];
        agl::TextureData * mGBufDepthView;
        char gap_8D8[1120];
        agl::TextureData * mGBufBaseColor;
        char gap_D40[1120];
        agl::TextureData * mGBufMotionVec;
        char gap_11A8[1120];
        const al::GraphicsSystemInfo *mGraphicsSystemInfo;
        void *field_1610;
        const agl::RenderTargetDepth *mRenderTargetDepth;
    };

    const agl::SamplerLocation &getSamplerLocationUniform0();
    const agl::SamplerLocation &getSamplerLocationUniform1();
    const agl::SamplerLocation &getSamplerLocationUniform2();
    const agl::SamplerLocation &getSamplerLocationUniform3();
    const agl::SamplerLocation &getSamplerLocationLinearDepth();
    const agl::SamplerLocation &getSamplerLocationGBufferBaseColor();
    const agl::SamplerLocation &getSamplerLocationGBufferNormal();
    const agl::SamplerLocation &getSamplerLocationCubeMapRoughness();
    const agl::SamplerLocation &getSamplerLocationMirrorTex();
    const agl::SamplerLocation &getSamplerLocationIndirectTex();
    const agl::SamplerLocation &getSamplerLocationDirLitTex();
    const agl::SamplerLocation &getSamplerLocationMaterialLight();
    const agl::SamplerLocation &getSamplerLocationShadowBuffer();
    const agl::SamplerLocation &getSamplerLocationMaterialLightSphere();
    const agl::SamplerLocation &getSamplerLocationShadowMap();
    const agl::SamplerLocation &getSamplerLocationCubeMapRoughnessRefract();
    const agl::SamplerLocation &getSamplerLocationProgTexture0();
    const agl::SamplerLocation &getSamplerLocationExposure();
    const agl::SamplerLocation &getSamplerLocationProgTextureCubemapGem0();
    const agl::SamplerLocation &getSamplerLocationProgTextureProcedural2D();
    const agl::SamplerLocation &getSamplerLocationProgTextureProcedural3D();
    const agl::SamplerLocation &getSamplerLocationFootPrintNormal();
    const agl::SamplerLocation &getSamplerLocationFootPrintBaseColor();
    const agl::SamplerLocation &getSamplerLocationHackStart();

}