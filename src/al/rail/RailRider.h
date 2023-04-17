#pragma once

#include "sead/math/seadVector.h"

#include "Rail.h"
#include "types.h"

namespace al
{

class RailRider {
public:
    void addSpeed(float speedInc);
    void setSpeed(float speedInc);
    void scaleSpeed(float factor);

    void move();
    void moveToBegin();
    void moveToGoal();
    void moveToNearestRail(sead::Vector3f const&);
    void moveToRailStart();
    void moveToRailEnd();
    void moveToRailPoint(int pointIdx);

    bool isReachedEdge() const;
    bool isReachedGoal() const;
    bool isReachedRailStart() const;
    bool isReachedRailEnd() const;

    void setMoveGoingStart();
    void setMoveGoingEnd();
    void reverse();

    void setCoord(float);
    void syncPosDir();

    al::Rail* mRail;                //0x00
    sead::Vector3f mPosition;       //0x08
    sead::Vector3f mDirection;      //0x14
    float mRailProgress;            //0x20
    float mMoveSpeed;               //0x24
    bool mIsMoveForwardOnRail;      //0x28
};

}