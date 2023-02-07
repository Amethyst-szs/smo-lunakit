#pragma once

#include "CameraPoser.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"

namespace alCameraPoserFunction {

    bool isPrePriorityDemo(al::CameraPoser const *);
    bool isPrePriorityDemo2(al::CameraPoser const *);
    bool isPrePriorityDemoTalk(al::CameraPoser const *);
    bool isPrePriorityDemoAll(al::CameraPoser const *);
    bool isPrePriorityEntranceAll(al::CameraPoser const *);
    bool isPrePriorityPlayer(al::CameraPoser const *);
    bool isEqualPreCameraName(al::CameraPoser const *, char const *);
    bool isPreCameraFixAbsolute(al::CameraPoser const *);
    bool isInvalidCollidePreCamera(al::CameraPoser const *);
    bool isInvalidKeepPreCameraDistance(al::CameraPoser const *);
    bool isInvalidKeepPreCameraDistanceIfNoCollide(al::CameraPoser const *);
    bool isValidResetPreCameraPose(al::CameraPoser const *);

    float getPreCameraSwingAngleH(al::CameraPoser const *);
    float getPreCameraSwingAngleV(al::CameraPoser const *);

    void calcCameraPose(sead::Quatf *, al::CameraPoser const *);

    void calcTargetTrans(sead::Vector3f *, al::CameraPoser const *);
    void calcTargetTransWithOffset(sead::Vector3f *, al::CameraPoser const *);

    void calcTargetPose(sead::Quatf *, al::CameraPoser const *);

    void setCameraPosToTarget(al::CameraPoser *);

    bool tryGetTargetRequestDistance(float *, al::CameraPoser const *);


};