#pragma once

#include <sead/math/seadVector.h>

#include "al/camera/CameraDirector.h"
#include "al/camera/Projection.h"
#include "gfx/seadProjection.h"

namespace al {
sead::Vector3f* getCameraUp(al::IUseCamera const*, int);
sead::Vector3f* getCameraPos(al::IUseCamera const*, int);
void getProjectionMtx(al::IUseCamera const*,int);
void getProjectionMtxPtr(al::IUseCamera const*,int);
sead::Projection *getProjectionSead(al::IUseCamera const*,int);
al::Projection *getProjection(al::IUseCamera const*,int);
}