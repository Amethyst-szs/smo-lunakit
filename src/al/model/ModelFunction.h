#pragma once

#include <math/seadBoundBox.h>
#include "ModelCtrl.h"

namespace alModelFunction {
    void calcBoundingBox(sead::BoundBox3<float> *,al::ModelCtrl const*);
    void calcBoundingBoxMtx(sead::Matrix34<float> *,al::ModelCtrl const*);
};