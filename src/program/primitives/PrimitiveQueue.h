
/*
    - Primitive Queue -

    This system is a simplification of sead's Primitive Renderer class, allowing pushing various objects to
    the list of objects to rendered that frame using primitive shapes.

    For more information about this class, read the docs:
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#primitives
*/

#pragma once

#include "sead/container/seadPtrArray.h"
#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadDisposer.h"

#include "PrimitiveTypes.h"

class PrimitiveQueue {
public:
    PrimitiveQueue(sead::Heap* heap);

    void render();

    void pushPoint(sead::Vector3f trans, float size, sead::Color4f col)
    {
        auto* entry = new (mHeap) PrimitiveTypePoint(trans, size, col);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }

    void pushLine(sead::Vector3f point1, sead::Vector3f point2, sead::Color4f col)
    {   
        auto* entry = new (mHeap) PrimitiveTypeLine(point1, point2, col);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushAxis(sead::Vector3f trans, float size)
    {   
        auto* entry = new (mHeap) PrimitiveTypeAxis(trans, size);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushArea(const char* gName, sead::Color4f frame, sead::Color4f fill)
    {   
        auto* entry = new (mHeap) PrimitiveTypeArea(gName, frame, fill);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushTriangle(al::Triangle tri, sead::Color4f color)
    {   
        auto* entry = new (mHeap) PrimitiveTypeTriangle(tri, color);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushHitSensor(al::LiveActor* actor, HitSensorRenderTypes sensorTypes, float opacity)
    {   
        auto* entry = new (mHeap) PrimitiveTypeHitSensor(actor, sensorTypes, opacity);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushBezierCurve(al::BezierCurve* curve, uint percision, sead::Color4f color)
    {   
        auto* entry = new (mHeap) PrimitiveTypeBezierCurve(curve, percision, color);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }
    
    void pushRail(al::Rail* rail, uint percision, sead::Color4f color)
    {   
        auto* entry = new (mHeap) PrimitiveTypeRail(rail, percision, color);
        mRenderQueue.pushBack((PrimitiveTypeBase*)entry);
    }

private:
    void emptyQueue();

    sead::Heap* mHeap = nullptr;
    sead::PtrArray<PrimitiveTypeBase> mRenderQueue;

    const int mMaxQueueSize = 0x400;
};