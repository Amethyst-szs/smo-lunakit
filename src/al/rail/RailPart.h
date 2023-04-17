#pragma once

#include "al/curves/LinearCurve.h"
#include "al/curves/BezierCurve.h"

namespace al {
    
class RailPart {
public:
    RailPart();
    void init(sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);

    void calcPos(sead::Vector3f* output, float percentage) const;
    void calcStartPos(sead::Vector3f* output) const;
    void calcEndPos(sead::Vector3f* output) const;
    void calcDir(sead::Vector3f* output, float percentage) const;
    void calcLength(float, float, int) const;
    void calcVelocity(sead::Vector3f*, float) const;
    void calcCurveParam(float) const;

    void calcNearestLength(float*, sead::Vector3f const&, float, float) const;
    void calcNearestPos(sead::Vector3f*, sead::Vector3f const&, float) const;
    void calcNearestParam(sead::Vector3f const&, float) const;

    void getPartLength() const;

    al::BezierCurve* mBezierCurve;      //0x00
    al::LinearCurve* mLinearCurve;      //0x08
    int mUnk;                           //0x10
};

} // namespace al