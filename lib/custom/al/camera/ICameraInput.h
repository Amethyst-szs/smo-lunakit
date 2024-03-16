#pragma once

#include <math/seadVector.h>

namespace al
{
    class ICameraInput
    {
    public:
        virtual void calcInputStick(sead::Vector2f* out) const
        {
            out->x = 0.0f;
            out->y = 0.0f;
        }
        virtual bool isTriggerReset() const { return false; }
        virtual bool isHoldZoom() const { return false; }
        virtual bool tryCalcSnapShotMoveStick(sead::Vector2f*) const { return false; }
        virtual bool isHoldSnapShotZoomIn() const { return false; }
        virtual bool isHoldSnapShotZoomOut() const { return false; }
        virtual bool isHoldSnapShotRollLeft() const { return false; }
        virtual bool isHoldSnapShotRollRight() const { return false; }
        virtual void calcGyroPose(sead::Vector3f* one, sead::Vector3f* two, sead::Vector3f* three) const
        {
            // Better way to do this?
            one->x = 0.0f;
            one->y = 0.0f;
            one->z = 0.0f;
            two->x = 0.0f;
            two->y = 0.0f;
            two->z = 0.0f;
            three->x = 0.0f;
            three->y = 0.0f;
            three->z = 0.0f;
        }
    };
}