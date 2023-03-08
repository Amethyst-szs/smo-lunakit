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
    PrimitiveQueue();

    void render();

    void pushEntry(PrimitiveTypeBase* entry) { mRenderQueue.pushBack(entry); }

private:
    void renderPoint(PrimitiveTypePoint* entry);
    void renderLine(PrimitiveTypeLine* entry);
    void renderAxis(PrimitiveTypeAxis* entry);
    void renderArea(PrimitiveTypeArea* entry);
    void renderTriangle(PrimitiveTypeTriangle* entry);

    void emptyQueue() { mRenderQueue.clear(); }

    sead::PtrArray<PrimitiveTypeBase> mRenderQueue;
};