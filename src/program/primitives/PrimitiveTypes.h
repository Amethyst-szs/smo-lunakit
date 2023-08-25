// Determines all different types of render queue objects and their parameters

#pragma once

#include "al/collision/Triangle.h"
#include "al/LiveActor/LiveActor.h"
#include "al/util/SensorUtil.h"

#include "sead/gfx/seadColor.h"
#include "sead/math/seadVector.h"

enum PrimitiveTypes {
    PRIM_NONE = -1,
    PRIM_POINT,
    PRIM_LINE,
    PRIM_AXIS,
    PRIM_AREA,
    PRIM_TRIANGLE,
    PRIM_HIT_SENSOR,
    PRIM_BEZIER_CURVE,
    PRIM_RAIL
};

class PrimitiveTypeBase {
public:
    PrimitiveTypeBase(PrimitiveTypes type) { mType = type; }
    virtual ~PrimitiveTypeBase() = default;

    virtual void render() = 0;
    
    PrimitiveTypes getType() { return mType; }

private:
    PrimitiveTypes mType = PrimitiveTypes::PRIM_NONE;
};

class PrimitiveTypePoint : public PrimitiveTypeBase {
public:
    PrimitiveTypePoint(sead::Vector3f trans, float size, sead::Color4f col)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_POINT)
    {
        mTranslation = trans;
        mSize = size;
        mColor = col;
    }
    ~PrimitiveTypePoint() override {}

    sead::Vector3f mTranslation;
    float mSize;
    sead::Color4f mColor;

    void render() override;
};

class PrimitiveTypeLine : public PrimitiveTypeBase {
public:
    PrimitiveTypeLine(sead::Vector3f point1, sead::Vector3f point2, sead::Color4f col, float pointSize1, float pointSize2)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_LINE)
    {
        mPoints[0] = point1;
        mPoints[1] = point2;
        mPointsSize[0] = pointSize1;
        mPointsSize[1] = pointSize2;
        mColor = col;
    }
    ~PrimitiveTypeLine() override {}

    sead::Vector3f mPoints[2];
    float mPointsSize[2];
    sead::Color4f mColor;

    void render() override;
};

class PrimitiveTypeAxis : public PrimitiveTypeBase {
public:
    PrimitiveTypeAxis(sead::Vector3f trans, float size)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_AXIS)
    {
        mTranslation = trans;
        mSize = size;
    }
    ~PrimitiveTypeAxis() override {}

    sead::Vector3f mTranslation;
    float mSize;

    void render() override;
};

class PrimitiveTypeBox : public PrimitiveTypeBase {
public:
    PrimitiveTypeBox(sead::Vector3f pos, sead::Vector3f size, sead::Color4f frame, sead::Color4f fill)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_AREA)
    {
        mPos = pos;
        mSize = size;
        mFrameColor = frame;
        mFillColor = fill;
    }
    ~PrimitiveTypeBox() override {}

    sead::Vector3f mPos;
    sead::Vector3f mSize;
    sead::Color4f mFrameColor;
    sead::Color4f mFillColor;

    void render() override;
};

class PrimitiveTypeArea : public PrimitiveTypeBase {
public:
    PrimitiveTypeArea(const char* gName, sead::Color4f frame, sead::Color4f fill)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_AREA)
    {
        mGroupName = gName;
        mFrameColor = frame;
        mFillColor = fill;
    }
    ~PrimitiveTypeArea() override {}

    const char* mGroupName;
    sead::Color4f mFrameColor;
    sead::Color4f mFillColor;

    void render() override;
};

class PrimitiveTypeTriangle : public PrimitiveTypeBase {
public:
    PrimitiveTypeTriangle(al::Triangle tri, sead::Color4f color)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_TRIANGLE)
    {
        mTriangle = tri;
        mColor = color;
    }
    ~PrimitiveTypeTriangle() override {}

    al::Triangle mTriangle;
    sead::Color4f mColor;

    void render() override;
};

enum HitSensorRenderTypes
{
    HitSensorType_NONE                      = 0,
    HitSensorType_ATTACK                    = 1 << 0,
    HitSensorType_EYE                       = 1 << 1,
    HitSensorType_NPC                       = 1 << 2,
    HitSensorType_TRAMPLE                   = 1 << 3,
    HitSensorType_BIND                      = 1 << 4,
    HitSensorType_ENEMYBODY                 = 1 << 5,
    HitSensorType_MAPOBJ                    = 1 << 6,
    HitSensorType_PLAYERALL                 = 1 << 7,
    HitSensorType_HOLDOBJ                   = 1 << 8,
    HitSensorType_MISC                      = 1 << 9,
    HitSensorType_ALL                       = HitSensorType_ATTACK | HitSensorType_EYE | HitSensorType_NPC | HitSensorType_TRAMPLE | HitSensorType_BIND | HitSensorType_ENEMYBODY | HitSensorType_MAPOBJ | HitSensorType_PLAYERALL | HitSensorType_HOLDOBJ | HitSensorType_MISC
};

class PrimitiveTypeHitSensor : public PrimitiveTypeBase {
public:
    PrimitiveTypeHitSensor(al::LiveActor* actor, HitSensorRenderTypes sensorTypes, float opacity)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_HIT_SENSOR)
    {
        mActor = actor;
        mSensorTypes = sensorTypes;
        mOpacity = opacity;
    }

    ~PrimitiveTypeHitSensor() override {}

    al::LiveActor* mActor;
    HitSensorRenderTypes mSensorTypes = HitSensorRenderTypes::HitSensorType_NONE;
    sead::Color4f mColor;
    float mOpacity;

    void render() override;
};

class PrimitiveTypeBezierCurve : public PrimitiveTypeBase {
public:
    PrimitiveTypeBezierCurve(al::BezierCurve* curve, uint percision, sead::Color4f color)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_BEZIER_CURVE)
    {
        mCurve = curve;
        mPercision = percision;
        mColor = color;
    }

    ~PrimitiveTypeBezierCurve() override {}

    al::BezierCurve* mCurve;
    uint mPercision;
    sead::Color4f mColor;

    void render() override;
};

class PrimitiveTypeRail : public PrimitiveTypeBase {
public:
    PrimitiveTypeRail(al::Rail* rail, uint percision, sead::Color4f color)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_RAIL)
    {
        mRail = rail;
        mPercision = percision;
        mColor = color;
    }

    ~PrimitiveTypeRail() override {}

    al::Rail* mRail;
    uint mPercision;
    sead::Color4f mColor;

    void render() override;
};