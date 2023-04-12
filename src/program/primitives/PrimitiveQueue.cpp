#include "PrimitiveQueue.h"

#include "sead/heap/seadDisposer.h"
#include "sead/gfx/seadPrimitiveRenderer.h"

#include "helpers/GetHelper.h"

PrimitiveQueue::PrimitiveQueue(sead::Heap* heap)
{
    mHeap = heap;
    mRenderQueue.allocBuffer(mMaxQueueSize, heap);
}

void PrimitiveQueue::render()
{
    if(mRenderQueue.isEmpty())
        return;
    
    HakoniwaSequence* seq = tryGetHakoniwaSequence();
    if(!seq) {
        emptyQueue();
        return;
    }
    
    al::Scene* curScene = tryGetScene(seq);
    const char* sceneNrv = typeid(*al::getCurrentNerve(seq)).name();

    // Check if the scene exists and if the current sequence nerve is save
    if(!isInScene(curScene) || strstr(sceneNrv, "Destroy") || strstr(sceneNrv, "DemoOpening")) {
        emptyQueue();
        return;
    }

    agl::DrawContext* drawContext = seq->getDrawInfo()->mDrawContext;
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    const sead::LookAtCamera* cam = al::getLookAtCamera(curScene, 0);
    const sead::Projection* proj = al::getProjectionSead(curScene, 0);

    renderer->setDrawContext(drawContext);
    renderer->setCamera(*cam);
    renderer->setProjection(*proj);
    renderer->setModelMatrix(sead::Matrix34f::ident);
    
    while (!mRenderQueue.isEmpty()) {
        renderer->begin();

        auto* entry = mRenderQueue[0];
        entry->render();
        delete entry;
        mRenderQueue.popFront();

        renderer->end();
    }
}

void PrimitiveQueue::emptyQueue()
{
    if(mRenderQueue.isEmpty())
        return;
    
    for(int i = 0; i < mRenderQueue.size(); i++) {
        auto* entry = mRenderQueue.at(i);
        delete entry;
    }

    mRenderQueue.clear();
}