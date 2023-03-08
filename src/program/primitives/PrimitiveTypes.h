// Determines all different types of render queue objects and their parameters

#pragma once

#include "al/collision/Triangle.h"

#include "sead/math/seadVector.h"
#include "sead/gfx/seadColor.h"

enum PrimitiveTypes {
    PRIM_NONE = -1,
    PRIM_POINT,
    PRIM_LINE,
    PRIM_AXIS,
    PRIM_AREA,
    PRIM_TRIANGLE
};


class PrimitiveTypeBase {
public:
    PrimitiveTypeBase(PrimitiveTypes type) { mType = type; }

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

    sead::Vector3f mTranslation;
    float mSize;
    sead::Color4f mColor;
};


class PrimitiveTypeLine : public PrimitiveTypeBase {
public:
    PrimitiveTypeLine(sead::Vector3f point1, sead::Vector3f point2, sead::Color4f col)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_LINE)
    {
        mPoints[0] = point1;
        mPoints[1] = point2;
        mColor = col;
    }

    sead::Vector3f mPoints[2];
    sead::Color4f mColor;
};


class PrimitiveTypeAxis : public PrimitiveTypeBase {
public:
    PrimitiveTypeAxis(sead::Vector3f trans, float size)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_AXIS)
    {
        mTranslation = trans;
        mSize = size;
    }

    sead::Vector3f mTranslation;
    float mSize;
};


class PrimitiveTypeArea : public PrimitiveTypeBase {
public:
    PrimitiveTypeArea(const char* groupName, sead::Color4f frameColor, sead::Color4f fillColor)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_AREA)
    {
        mGroupName = groupName;
        mFrameColor = frameColor;
        mFillColor = fillColor;
    }

    const char* mGroupName;
    sead::Color4f mFrameColor;
    sead::Color4f mFillColor;
};


class PrimitiveTypeTriangle : public PrimitiveTypeBase {
public:
    PrimitiveTypeTriangle(al::Triangle tri, sead::Color4f color)
        : PrimitiveTypeBase(PrimitiveTypes::PRIM_TRIANGLE)
    {
        mTriangle = tri;
        mColor = color;
    }

    al::Triangle mTriangle;
    sead::Color4f mColor;
};