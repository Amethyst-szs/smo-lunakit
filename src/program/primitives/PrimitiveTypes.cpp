#include "PrimitiveTypes.h"

void PrimitiveTypePoint::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawSphere4x8(mTranslation, mSize, mColor);
}

void PrimitiveTypeLine::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawLine(mPoints[0], mPoints[1], mColor);
}

void PrimitiveTypeAxis::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawAxis(mTranslation, mSize);
}

void PrimitiveTypeArea::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    al::Scene* scene = tryGetScene();

    al::AreaObjGroup* group = scene->mLiveActorKit->mAreaObjDirector->getAreaObjGroup(mGroupName);
    if(!group)
        return;
    
    sead::Color4f cyl = mFrameColor;
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
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, mFrameColor);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeCenter")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, 0, 0), scale * 1000.0f, mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, 0, 0), scale * 1000.0f, mFrameColor);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeTop")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, mFillColor);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, mFrameColor);
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

void PrimitiveTypeTriangle::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    renderer->drawLine(mTriangle.mPosition1, mTriangle.mPosition2, mColor);
    renderer->drawLine(mTriangle.mPosition2, mTriangle.mPosition3, mColor);
    renderer->drawLine(mTriangle.mPosition3, mTriangle.mPosition1, mColor);
    
    renderer->drawSphere4x8(mTriangle.mPosition1, 9.f, mColor);
    renderer->drawSphere4x8(mTriangle.mPosition2, 9.f, mColor);
    renderer->drawSphere4x8(mTriangle.mPosition3, 9.f, mColor);
}