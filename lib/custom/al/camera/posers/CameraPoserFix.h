#pragma once

#include "al/camera/CameraPoser.h"
#include "al/camera/alCameraPoserFunction.h"
#include "al/util.hpp"

#include "sead/math/seadVector.h"

namespace al {
    class CameraPoserFix : public CameraPoser {
        public:
            CameraPoserFix(char const*);
            virtual void init(void) override;
            virtual void loadParam(al::ByamlIter const&) override;
            virtual void start(al::CameraStartInfo const&) override;
            virtual void update(void) override;

            void initCameraPosAndLookAtPos(sead::Vector3f const&,sead::Vector3f const&);
            const char *getFixAbsoluteCameraName(void);
            const char *getFixDoorwayCameraName(void);

            sead::Vector3f mLookAtPos; // 0x140
            float mDistance;
            float mAngleV;
            float mAngleH;
            bool mIsCalcNearestAtFromPreAt;
            sead::Vector3f mPreLookAtPos;
    };
}