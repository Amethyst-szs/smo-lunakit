#pragma once

#include <gfx/api.h>
#include <math/seadVector.h>
#include <types.h>
namespace nn {

namespace g3d {
class MaterialObj;
class ResVertex;
class ResMesh;
}  // namespace g3d

}  // namespace nn
// TODO: Someone should add this to sead!
namespace sead {
class GraphicsContext;
}  // namespace sead

namespace agl {
class ConstGPUMemVoidAddr;
}  // namespace agl

namespace al {
class ActorInitInfo;
class LiveActor;
class FootPrintRequestInfo;
class Scene;
class ModelCtrl;
class ModelShaderHolder;

void setDepthFuncNearDraw(sead::GraphicsContext* context);
void setDepthFuncFarDraw(sead::GraphicsContext* context);
void setDepthFuncNearDraw(sead::GraphicsContext* context);
void setDepthFuncFarDraw(sead::GraphicsContext* context);
bool getAlphaTestEnable(nn::g3d::MaterialObj* material);
}  // namespace al

class alGraphicsFunction {
public:
    static void registerGraphicsPreset(const char*, const char*, const char*, const al::ActorInitInfo&, bool);
    static void requestGraphicsPreset(const al::LiveActor*, const char*, s32, s32, s32, const sead::Vector3f&);
    static void appearFootPrint(const al::LiveActor*, al::FootPrintRequestInfo*);
    static void disappearFootPrint(const al::LiveActor*, al::FootPrintRequestInfo*);
    static void setRainControl(const al::LiveActor*, f32);
    static void setRainUpdateFlag(al::Scene*, bool);
    static bool isEnableRain(al::Scene*);
    static void setFogNoiseUpdateFlag(al::Scene*, bool);
    static void getDirectionalLightDir(const al::LiveActor*);
    static void calcDirectionalLightDir(const al::LiveActor*);
    static void getDepthShadowFarLength(const al::LiveActor*);
    static void invalidateCameraBlurSystem(al::Scene*);
    static void validateCameraBlurSystem(al::Scene*);
    static void invalidateOcclusionCullingSystem(al::Scene*);
    static void validateOcclusionCullingSystem(al::Scene*);
    static bool isGraphicsQualityModeConsole(const al::LiveActor*);
    static bool isGraphicsQualityModeHandheld(const al::LiveActor*);
    static void forceGraphicsQualityModeConsole(al::Scene*);
    static void forceGraphicsQualityModeHandheld(al::Scene*);
    static void forceGraphicsQualityModeSnapShot(al::Scene*);
    static void unforceGraphicsQualityMode(al::Scene*);
    static void validateModelLodAll(al::Scene*);
    static void invalidateModelLodAll(al::Scene*);
    static void setSphereMapUpdateEveryFrame(al::Scene*, const sead::Vector3f&);
    static void setMaterialLightUpdateBaseAngleChanged(al::Scene*, bool);
    static void requestChangeShaderVariation(const al::LiveActor*, const char*, const char*, bool);
    static void requestChangeShaderVariation(al::ModelCtrl*, s32, al::ModelShaderHolder*, const char*, const char*, bool);
    static void requestChangeShaderVariation(al::ModelCtrl*, al::ModelShaderHolder*, const char*, const char*, bool);
    static void requestChangeShaderVariationWithoutForward(const al::LiveActor*, const char*, const char*, bool);
    static void requestUpdateMaterialInfo(al::Scene*);
    static void validateGpuStressAnalyzer(al::Scene*);
    static void invalidateGpuStressAnalyzer(al::Scene*);
    static bool isValidGpuStressAnalyzer(al::Scene*);
    static void calcVertexBufferGPUAddress(const nn::g3d::ResVertex&, s32);
    static void calcIndexBufferGPUAddress(nn::g3d::ResMesh&);
};