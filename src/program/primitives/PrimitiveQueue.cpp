#include "PrimitiveQueue.h"

PrimitiveQueue::PrimitiveQueue()
{
    sead::Heap* heap = al::getStationedHeap();
    mRenderQueue.allocBuffer(0x100, heap);
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
    
    agl::DrawContext* drawContext = seq->getDrawInfo()->mDrawContext;
    al::Scene* curScene = tryGetScene(seq);

    // Check if the scene exists and if the current sequence nerve is save
    if(!isInScene(curScene) || strstr(typeid(*al::getCurrentNerve(seq)).name(), "Destroy")) {
        emptyQueue();
        return;
    }

    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    const sead::LookAtCamera* cam = al::getLookAtCamera(curScene, 0);
    const sead::Projection* proj = al::getProjectionSead(curScene, 0);

    renderer->setDrawContext(drawContext);
    renderer->setCamera(*cam);
    renderer->setProjection(*proj);
    renderer->setModelMatrix(sead::Matrix34f::ident);
    renderer->begin();
    
    for(int i = 0; i < mRenderQueue.size(); i++) {
        auto* entry = mRenderQueue.at(i);

        switch(entry->getType()) {
            case PrimitiveTypes::PRIM_NONE:
                Logger::log("Item in primitive render queue has type NONE?\n");
                break;

            case PrimitiveTypes::PRIM_POINT:
                renderPoint((PrimitiveTypePoint*)entry);
                break;

            case PrimitiveTypes::PRIM_LINE:
                renderLine((PrimitiveTypeLine*)entry);
                break;

            case PrimitiveTypes::PRIM_AXIS:
                renderAxis((PrimitiveTypeAxis*)entry);
                break;

            case PrimitiveTypes::PRIM_AREA:
                renderArea((PrimitiveTypeArea*)entry);
                break;

            case PrimitiveTypes::PRIM_TRIANGLE:
                renderTriangle((PrimitiveTypeTriangle*)entry);
                break;
        }

        delete mRenderQueue.at(i);
    }

    emptyQueue();
    renderer->end();
}

void PrimitiveQueue::renderPoint(PrimitiveTypePoint* entry)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawSphere4x8(entry->mTranslation, entry->mSize, entry->mColor);
}

void PrimitiveQueue::renderLine(PrimitiveTypeLine* entry)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawLine(entry->mPoints[0], entry->mPoints[1], entry->mColor);
}

void PrimitiveQueue::renderAxis(PrimitiveTypeAxis* entry)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawAxis(entry->mTranslation, entry->mSize);
}

void PrimitiveQueue::renderArea(PrimitiveTypeArea* entry)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    al::Scene* scene = tryGetScene();

    al::AreaObjGroup* group = scene->mLiveActorKit->mAreaObjDirector->getAreaObjGroup(entry->mGroupName);
    if(!group)
        return;
    
    sead::Color4f cyl = entry->mFrameColor;
    cyl.a *= 0.11f;
    
    for (int i = 0; i < group->mCurCount; i++) {
        al::AreaObj* area = group->mAreas[i];
        const char* shapeType;
        al::tryGetAreaObjStringArg(&shapeType, area, "ModelName");

        sead::Vector3f scale = area->mAreaShape->mScale;
        sead::Vector3f pos;
        pos.x = area->mAreaMtx.m[0][3];
        pos.y = area->mAreaMtx.m[1][3];
        pos.z = area->mAreaMtx.m[2][3];
        renderer->setModelMatrix(area->mAreaMtx);

        if (al::isEqualString(shapeType, "AreaCubeBase")) { // origin is at the bottom
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, entry->mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, entry->mFrameColor);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeCenter")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, 0, 0), scale * 1000.0f, entry->mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, 0, 0), scale * 1000.0f, entry->mFrameColor);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeTop")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, entry->mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, entry->mFrameColor);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaSphere"))
            renderer->drawSphere8x16(sead::Vector3f(0, 0, 0), scale.x * 1000, cyl);
        
        if (al::isEqualString(shapeType, "AreaCylinder")) // origin is at the bottom
            renderer->drawCylinder32(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale.x * 1000, scale.y * 1000, cyl);
        
        if (al::isEqualString(shapeType, "AreaCylinderCenter"))
            renderer->drawCylinder32(sead::Vector3f(0, 0, 0), scale.x * 1000, scale.y * 1000, cyl);

        if (al::isEqualString(shapeType, "AreaCylinderTop")) 
            renderer->drawCylinder32(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale.x * 1000, scale.y * 1000, cyl);
    }

    renderer->setModelMatrix(sead::Matrix34f::ident);
}

void PrimitiveQueue::renderTriangle(PrimitiveTypeTriangle* entry)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    renderer->drawLine(entry->mTriangle.mPosition1, entry->mTriangle.mPosition2, entry->mColor);
    renderer->drawLine(entry->mTriangle.mPosition2, entry->mTriangle.mPosition3, entry->mColor);
    renderer->drawLine(entry->mTriangle.mPosition3, entry->mTriangle.mPosition1, entry->mColor);
    
    renderer->drawSphere4x8(entry->mTriangle.mPosition1, 9.f, entry->mColor);
    renderer->drawSphere4x8(entry->mTriangle.mPosition2, 9.f, entry->mColor);
    renderer->drawSphere4x8(entry->mTriangle.mPosition3, 9.f, entry->mColor);
}