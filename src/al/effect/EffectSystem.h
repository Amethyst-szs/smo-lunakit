#pragma once

#include <math/seadMatrix.h>
#include "EffectSystemInfo.h"

namespace sead {
class Heap;
}  // namespace sead

namespace agl {
class DrawContext;

namespace sdw {
class DepthShadow;
}  // namespace sdw

}  // namespace agl

namespace al {
class ExecuteDirector;
class CameraDirector;
class CollisionCodeList;
class GraphicsSystemInfo;
class EffectCameraHolder;

class EffectSystem {
private:
    void* field_0;
    al::EffectSystemInfo mEffectSystemInfo;
    al::EffectCameraHolder* mEffectCameraHolder;
    s32 field_30;
    void* field_38;
    void* field_40;
    void* field_48;
    void* field_50;
    void* field_58;
    void* field_60;
    bool field_68;
    bool mIsUpdateKit;
    // unfinished memebers, this class is huge and i don't have the time or motivation to find the types of everything right now.

public:
    EffectSystem();
    void getDefaultDataBaseResourcePath();
    void getDefaultPtclResourcePath();
    void getDefaultPtclPatchResourcePath();
    void createSystem(agl::DrawContext*, sead::Heap*);
    void createSystemWithPatchResouce(agl::DrawContext*, sead::Heap*);
    void loadEffectResource(al::EffectSystem*);
    void loadPtclResource(sead::Heap*);
    void initializeSystem(agl::DrawContext*, sead::Heap*);
    void initializeSystemWithPatchResouce(agl::DrawContext*, sead::Heap*);
    bool isEnableBatchCompute();
    void getPauseForceCalcFrame();
    void setDrawContext(agl::DrawContext*);
    void addResourcePath(const char*);
    void init();
    void loadDbResource(sead::Heap*);
    void initScene();
    void endInit();
    void startScene(al::ExecuteDirector*);
    void preprocess();
    void postprocess();
    void endScene();
    void setCameraDirector(al::CameraDirector*);
    void setMaterialCodeList(al::CollisionCodeList*);
    void calcParticle(u64);
    void setGraphicsSystemInfo(const al::GraphicsSystemInfo*);
    void updateEffect(const char*) const;
    void findGroupDrawer(const char*) const;
    void calcEffectCompute() const;
    void drawEffectWithRenderPathAndCamPos(const sead::Matrix44f&, const sead::Matrix34f&, const sead::Vector3f&, f32, f32, f32, const char*,
                                           u32) const;
    void drawEffectWithRenderPath(const sead::Matrix44f&, const sead::Matrix34f&, f32, f32, f32, const char*, u32) const;
    void calcShadowClipVolume(agl::sdw::DepthShadow*, const char*, u32) const;
    void addCalcEffect(u64);
    bool isHasRenderingEmitter(u32) const;
    void checkCalculateFlag(s32);
    void calcParticle(s32);
    void calcChildParticle(s32);

    void setIsUpdateKit(bool isUpdateKit) { mIsUpdateKit = isUpdateKit; }
};
}  // namespace al