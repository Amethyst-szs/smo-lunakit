#pragma once

#include "al/camera/CameraDirector.h"
#include "sead/math/seadVector.h"

#include "types.h"

namespace al {

class SceneCameraInfo;

uint calcCameraPosToWorldPosDirFromScreenPos(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, float);
uint calcCameraPosToWorldPosDirFromScreenPos(sead::Vector3f* output, al::SceneCameraInfo const*, sead::Vector2f const&, float, int);
uint calcCameraPosToWorldPosDirFromScreenPos(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, sead::Vector3f const&);
uint calcCameraPosToWorldPosDirFromScreenPos(sead::Vector3f* output, al::SceneCameraInfo const*, sead::Vector2f const&, sead::Vector3f const&, int);
void calcCameraPosToWorldPosDirFromScreenPosSub(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, float);
void calcCameraPosToWorldPosDirFromScreenPosSub(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, sead::Vector3f const&);

void calcLayoutPosFromScreenPos(sead::Vector2f* output, sead::Vector2f const&);
void calcLayoutPosFromWorldPosWithClampByScreen(sead::Vector3f* output, al::IUseCamera const*, sead::Vector3f const&);

void calcLineCameraToWorldPosFromScreenPos(sead::Vector3f* output, sead::Vector3f*, al::IUseCamera const*, sead::Vector2f const&, float, float);
void calcLineCameraToWorldPosFromScreenPos(sead::Vector3f* output, sead::Vector3f*, al::IUseCamera const*, sead::Vector2f const&);
void calcLineCameraToWorldPosFromScreenPos(sead::Vector3f* output, sead::Vector3f*, al::SceneCameraInfo const*, sead::Vector2f const&, float, float, int);
void calcLineCameraToWorldPosFromScreenPos(sead::Vector3f* output, sead::Vector3f*, al::SceneCameraInfo const*, sead::Vector2f const&, int);
void calcLineCameraToWorldPosFromScreenPosSub(sead::Vector3f* output, sead::Vector3f*, al::IUseCamera const*, sead::Vector2f const&, float, float);
void calcLineCameraToWorldPosFromScreenPosSub(sead::Vector3f* output, sead::Vector3f*, al::IUseCamera const*, sead::Vector2f const&);

void calcScreenPosFromLayoutPos(sead::Vector2f* output, sead::Vector2f const&);
void calcScreenPosFromWorldPos(sead::Vector2f* output, al::IUseCamera const*, sead::Vector3f const&);
void calcScreenPosFromWorldPosSub(sead::Vector2f* output, al::IUseCamera const*, sead::Vector3f const&);

int calcScreenRadiusFromWorldRadius(sead::Vector3f const&, al::IUseCamera const*, float); // Return type may be incorrect
int calcScreenRadiusFromWorldRadiusSub(sead::Vector3f const&, al::IUseCamera const*, float); // Return type may be incorrect

bool calcWorldPosFromScreen(sead::Vector3f* output, sead::Vector2f const&, sead::Matrix34f const&, float);
void calcWorldPosFromScreenPos(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, float);
void calcWorldPosFromScreenPos(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, sead::Vector3f const&);
void calcWorldPosFromScreenPos(sead::Vector3f* output, al::SceneCameraInfo const*, sead::Vector2f const&, float, int);
void calcWorldPosFromScreenPos(sead::Vector3f* output, al::SceneCameraInfo const*, sead::Vector2f const&, sead::Vector3f const&, int);
void calcWorldPosFromScreenPosSub(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, float);
void calcWorldPosFromScreenPosSub(sead::Vector3f* output, al::IUseCamera const*, sead::Vector2f const&, sead::Vector3f const&);

void calcTouchScreenPos(sead::Vector2f* output);

} // namespace al