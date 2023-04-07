#pragma once

#include "sead/math/seadVector.h"

namespace al {
    
class LinearCurve {
public:
    LinearCurve();

    void set(sead::Vector3f const& startPos, sead::Vector3f const& endPos);

    void calcPos(sead::Vector3f* output, float percentage) const;
    void calcStartPos(sead::Vector3f* output) const;
    void calcEndPos(sead::Vector3f* output) const;
    void calcLength(float startPercentage, float endPercentage) const;
    void calcVelocity(sead::Vector3f* output, float) const;
    void calcCurveParam(float) const;

    void calcNearestPos(sead::Vector3f*, sead::Vector3f const&) const;
    float calcNearestLength(float*, sead::Vector3f const&, float) const;
    float calcNearestParam(sead::Vector3f const&) const;

    sead::Vector3f mStartPos;           //0x00
    sead::Vector3f mOffsetToEndPos;     //0x0C
    float mLength;                      //0x18
};

} // namespace al