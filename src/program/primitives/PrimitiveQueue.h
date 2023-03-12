
/*
    - Primitive Queue -

    This system is a simplification of sead's Primitive Renderer class, allowing pushing various objects to
    the list of objects to rendered that frame using primitive shapes.

    For more information about this class, read the docs:
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#primitives
*/

#pragma once

#include "al/util.hpp"
#include "al/collision/alCollisionUtil.h"
#include "al/scene/Scene.h"

#include "game/StageScene/StageScene.h"

#include "sead/container/seadPtrArray.h"
#include "sead/heap/seadDisposer.h"
#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/gfx/seadPrimitiveRenderer.h"

#include "logger/Logger.hpp"

#include "GetterUtil.h"

#include "PrimitiveTypes.h"

class PrimitiveQueue {
public:
    PrimitiveQueue(sead::Heap* heap);

    void render();

    void pushEntry(PrimitiveTypeBase* entry) { mRenderQueue.pushBack(entry); }

private:
    void renderPoint(PrimitiveTypePoint* entry);
    void renderLine(PrimitiveTypeLine* entry);
    void renderAxis(PrimitiveTypeAxis* entry);
    void renderArea(PrimitiveTypeArea* entry);
    void renderTriangle(PrimitiveTypeTriangle* entry);

    void emptyQueue();

    sead::Heap* mHeap = nullptr;
    sead::PtrArray<PrimitiveTypeBase> mRenderQueue;
};