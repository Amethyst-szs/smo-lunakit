#pragma once

#include "al/actor/Placement.h"

#include "RailPart.h"

namespace al {
    
class Rail {
public:
    Rail();
    void init(al::PlacementInfo const&);

    void calcPos(sead::Vector3f* output, float) const;
    void calcPosDir(sead::Vector3f*, sead::Vector3f*, float) const;
    void calcDirection(sead::Vector3f*, float) const;
    void calcRailPointPos(sead::Vector3f* output, int idx) const;
    int calcRailPointNum(float, float) const;

    void calcNearestRailPointNo(int* output, sead::Vector3f const&) const;
    void calcNearestRailPointPos(sead::Vector3f* output, sead::Vector3f const&) const;
    void calcNearestRailPointPosFast(sead::Vector3f* output, unsigned int*, sead::Vector3f const&) const;
    float calcNearestRailPos(sead::Vector3f* output, sead::Vector3f const&, float) const;
    float calcNearestRailPosCoord(sead::Vector3f const&, float) const;
    float calcNearestRailPosCoord(sead::Vector3f const&, float, float*) const;

    unsigned long getIncludedSection(al::RailPart const**, float*, float) const; // Return type is most likely wrong
    long getIncludedSectionIndex(float) const;
    void getIncludedSectionLength(float*, float*, float) const;
    float getLengthToPoint(int) const; // Return type may be incorrect
    float getPartLength(int) const;
    float getTotalLength() const;

    bool isBezierRailPart(int idx) const;
    bool isIncludeBezierRailPart() const;
    bool isNearRailPoint(float, float) const;

    unsigned long normalizeLength(float) const; // Return type may be incorrect

    al::PlacementInfo* mPlacementInfo;  //0x00
    al::RailPart** mRailParts;          //0x08
    int mUnk;                           //0x10
    int mRailPoints;                    //0x14
    bool mIsClosedLoop;                 //0x18
};

} // namespace al