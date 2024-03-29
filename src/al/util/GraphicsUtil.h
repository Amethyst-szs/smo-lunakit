#pragma once

namespace sead {
class LookAtCamera;
class Projection;
}  // namespace sead

namespace al {
class IUseCamera;
class Scene;

void updateKitListPrev(Scene*);
void updateKitList(Scene*, const char*);
void updateKitListPost(Scene*);
void updateKitTable(al::Scene*, const char*);

sead::LookAtCamera* getLookAtCamera(al::IUseCamera const*, int);
}  // namespace al

// TODO: get this out of here
namespace rs {
void requestGraphicsPresetAndCubeMapPause(const al::Scene*);
}  // namespace rs
