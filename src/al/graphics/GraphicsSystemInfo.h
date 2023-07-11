#pragma once

#include "al/hio/HioNode.h"

//#include "types.h"
#define _BYTE unsigned char
#define __int64 long long

#include "al/area/AreaObjDirector.h"

namespace agl {
    class DrawContext;

    namespace cull {
        class OcclusionQueryDrawer {
            void drawDebug(agl::DrawContext *, int) const;
        };
    }
    namespace sdw {
        class PrimitiveOcclusion {
            public:
            void drawDebug(agl::DrawContext *, int) const;
        };
    }
    namespace pfx {
        class FilterAA;
    }
}

namespace al {
    class GraphicsInitArg;
    class DepthOfFieldDrawer;
    class BloomDirector;
    class CubeMapDirector;
    class DirectionalLightKeeper;
    class GraphicsAreaDirector : public al::IUseHioNode, public al::IUseAreaObj {

    };
    class GraphicsPresetDirector;
    class DemoGraphicsController;
    class RadialBlurDirector;
    class PrePassLightKeeper;
    class ShaderEnvTextureKeeper;
    class ShadowDirector;
    class GraphicsQualityController;
    class ShaderMirrorDirector;
    class GraphicsParamRequesterImpl;
    class FlareFilterDirector;
    class GodRayDirector;
    class FogDirector;
    class OccludedEffectDirector;
    class LightStreakDirector;
    class HdrCompose;
    class SSIIKeeper;
    class RandomTextureKeeper;
    class WorldAODirector;
    class PointSpriteCursorHolder;
    class MaterialLightDirector;
    class MaterialCategoryKeeper;
    class SkyDirector;
    class ShaderHolder;
    class OcclusionCullingJudge;
    class VignettingDrawer;
    class CameraBlurController;
    class ThunderRenderKeeper;
    class StarrySky;
    class NoiseTextureKeeper;
    class CloudRenderKeeper;
    class GpuMemAllocator;
    class FootPrintTextureKeeper;
    class ProgramTextureKeeper;
    class RippleTextureKeeper;
    class ViewRenderer;
    class SubCameraRenderer;
    class TemporalInterlace;
    class PeripheryRendering;
    class PostProcessingFilter;
    class GraphicsParamFilePath;
    class AreaObjDirector;
    class ExecuteDirector;
    class EffectSystem;
    class SceneCameraInfo;
    class VastGridMeshDirector;
    class FullScreenTriangle;
    class ReducedBufferRenderer;
    class ModelOcclusionCullingDirector;
    class ModelLodAllCtrl;
    class ModelShaderHolder;
    class PrepassTriangleCulling;

    class GraphicsSystemInfo
    {
    public:
    __int64 *field_0;
    __int64 *field_8;
    __int64 *field_10;
    int field_18;
    int field_1C;
    const al::GraphicsInitArg &mGraphicsInitArg; // this might give you trouble in IDA
    int mDisplayWidth;
    int mDisplayHeight;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54; // 54
    al::DepthOfFieldDrawer *mDepthOfFieldDrawer; //0x58
    __int64 *field_68;
    al::BloomDirector *mBloomDirector; // 0x68
    al::CubeMapDirector *mCubeMapDirector; // 0x70
    al::DirectionalLightKeeper *mDirectionalLightKeeper;
    al::GraphicsAreaDirector *mGraphicsAreaDirector;
    al::GraphicsPresetDirector *mGraphicsPresetDirector;
    al::DemoGraphicsController *mDemoGraphicsController;
    al::RadialBlurDirector *mRadialBlurDirector;
    al::PrePassLightKeeper *mPrePassLightKeeper;
    al::ShaderEnvTextureKeeper *mShaderEnvTextureKeeper;
    al::ShadowDirector *mShadowDirector;
    al::DepthOfFieldDrawer *mDepthOfFieldDrawer2;
    al::GraphicsQualityController *mGraphicsQualityController;
    al::ShaderMirrorDirector *mShaderMirrorDirector;
    al::GraphicsParamRequesterImpl *field_D0;
    al::GraphicsParamRequesterImpl *field_D8;
    al::FlareFilterDirector *mFlareFilterDirector;
    al::GodRayDirector *mGodRayDirector;
    al::FogDirector *mFogDirector;
    al::OccludedEffectDirector *mOccludedEffectDirector;
    al::LightStreakDirector *mLightStreakDirector;
    al::HdrCompose *mHdrCompose;
    al::SSIIKeeper *mSSIIKeeper;
    agl::sdw::PrimitiveOcclusion *mPrimitiveOcclusion;
    _BYTE gap_120[240];
    __int64 field_210;
    al::RandomTextureKeeper *mRandomTextureKeeper;
    al::WorldAODirector *mWorldAODirector;
    al::PointSpriteCursorHolder *mPointSpriteCursorHolder;
    al::MaterialLightDirector *mMaterialLightDirector;
    al::MaterialCategoryKeeper *mMaterialCategoryKeeper;
    al::SkyDirector *mSkyDirector;
    al::ShaderHolder *mShaderHolder; // 0x248
    al::OcclusionCullingJudge *mOcclusionCullingJudge;
    al::VignettingDrawer *mVignettingDrawer;
    al::CameraBlurController *mCameraBlurController;
    al::ThunderRenderKeeper *mThunderRenderKeeper;
    al::StarrySky *mStarrySky;
    al::NoiseTextureKeeper *mNoiseTextureKeeper;
    al::CloudRenderKeeper *mCloudRenderKeeper;
    al::GpuMemAllocator *mGpuMemAllocator;
    al::FootPrintTextureKeeper *mFootPrintTextureKeeper;
    al::ProgramTextureKeeper *mProgramTextureKeeper;
    al::RippleTextureKeeper *mRippleTextureKeeper;
    __int64 *field_2A8; // 0x2A8
    al::ViewRenderer *mViewRenderer;
    al::SubCameraRenderer *mSubCameraRenderer;
    al::TemporalInterlace *mTemporalInterlace;
    al::PeripheryRendering *mPeripheryRendering;
    al::PostProcessingFilter *mPostProcessingFilter;
    __int64 field_2D8;
    __int64 field_2E0;
    __int64 field_2E8;
    __int64 field_2F0;
    agl::pfx::FilterAA *mAntiAliasing; // 0x2F8
    __int64 field_300;
    __int64 field_308;
    al::GraphicsParamFilePath *mGraphicsParamFilePath; // 0x310
    _BYTE gap_318[1528];
    __int64 field_910; // 0x910
    __int64 field_918;
    __int64 field_920;
    al::AreaObjDirector *mAreaObjDirector;
    al::ExecuteDirector *mExecuteDirector;
    al::EffectSystem *mEffectSystem;
    al::SceneCameraInfo *mSceneCameraInfo;
    __int64 field_948;
    __int64 field_950;
    __int64 field_958;
    __int64 field_960;
    al::VastGridMeshDirector *mVastGridMeshDirector;
    al::FullScreenTriangle *mFullScreenTriangle;
    __int64 field_978;
    al::ReducedBufferRenderer *mReducedBufferRenderer;
    al::ModelOcclusionCullingDirector *mModelOcclusionCullingDirector;
    al::ModelLodAllCtrl *mModelLodAllCtrl;
    al::ModelShaderHolder *mModelShaderHolder;
    al::PrepassTriangleCulling *mPrepassTriangleCulling;
    __int64 field_9A8; // 0x9A8
    __int64 field_9B0;
};
}