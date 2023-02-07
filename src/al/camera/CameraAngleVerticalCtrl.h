#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/nerve/NerveExecutor.h"
#include "sead/math/seadVector.h"

struct CameraAngleUpdateInfo;

namespace al {
    class CameraAngleVerticalCtrl : public al::NerveExecutor {
    public:
        CameraAngleVerticalCtrl(void);
        virtual ~CameraAngleVerticalCtrl();
      
        void getInitDefaultAngleDegree(void);
        void loadParam(al::ByamlIter const&);
        void start(sead::Vector3f const&);
        void startUserCtrl(void);
        void update(CameraAngleUpdateInfo const&);
        void getDefaultAngleDegree(void);
        void setAngleDegree(float);
        void startTargetInterpole(float);
        void startTargetInterpoleByStep(float,int);
        void startResetInterpole(void);
        void startResetInterpoleByStep(int);
        void chaseToTargetDegree(float);
        void chaseToTargetDegreeBySpeed(float,float);
        bool isFixInRange(void) const;
        void setRailAngleDegreeRangeAndInterp(float,float,int);
        void resetRailAngleDegreeRange(void);
        void startWaterCtrl(int);
        void invalidateAutoResetLowAngleV(void);
        void startSnap(float);
        void endSnap(void);

        void exeUserCtrl(void);
        void exeWaterCtrl(void);
        void exeHackFlyerCtrl(void);
        void exeInterp(void);
        void exeSnapStart(void);
        void exeSnap(void);
        void exeSnapEnd(void);

    };
}