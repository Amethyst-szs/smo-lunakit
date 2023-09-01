#pragma once

#include "math/seadMatrix.h"
#include "math/seadVector.h"
#include "prim/seadSafeString.h"

struct Gyro {
    sead::Matrix33f mDirection = sead::Matrix33f::ident;
    sead::Vector3f mAngularV = sead::Vector3f::zero;
};

struct InputFrame {
    u32 mStep = 0;
    bool mSecondPlayer = false;
    u32 mButtons = 0;
    sead::Vector2f mLeftStick = sead::Vector2f::zero;
    sead::Vector2f mRightStick = sead::Vector2f::zero;
    sead::Vector3f mLeftAccel = sead::Vector3f::zero;
    sead::Vector3f mRightAccel = sead::Vector3f::zero;
    Gyro mLeftGyro;
    Gyro mRightGyro;
};

struct Script {
    static const u32 magic = 0x424f4f42;  // BOOB
    u32 mMagic;
    u32 mFrameCount;  // how many individual lines there are, NOT just the highest step number
    bool mIsTwoPlayer;
    s32 mScenarioNo;
    char mChangeStageName[0x80];
    char mChangeStageId[0x80];
    sead::Vector3f mStartPosition;
    InputFrame mFrames[];
};