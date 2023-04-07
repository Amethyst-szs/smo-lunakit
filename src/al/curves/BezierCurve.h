#pragma once

#include "sead/math/seadVector.h"

namespace al {
    
class BezierCurve {
public:
    BezierCurve();
    
    void set(sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);

    void calcPos(sead::Vector3f* output, float percentage) const;
    void calcStartPos(sead::Vector3f* output) const;
    void calcCtrlPos1(sead::Vector3f* output) const;
    void calcCtrlPos2(sead::Vector3f* output) const;
    void calcVelocity(sead::Vector3f* output, float) const;
    
    void calcLength(float, float, int) const;
    float calcDeltaLength(float) const;

    void calcNearestPos(sead::Vector3f*, sead::Vector3f const&, float) const;
    float calcNearestLength(float*, sead::Vector3f const&, float, float) const;
    float calcNearestParam(sead::Vector3f const&, float) const;

    sead::Vector3f mStartPos;           //0x00
    sead::Vector3f mControlPoint1;      //0x0C
    sead::Vector3f mControlPoint2;      //0x18
    sead::Vector3f mControlPoint3;      //0x24 (May be end point, not a third control point?)
    float mLength;                      //0x30
};

} // namespace al