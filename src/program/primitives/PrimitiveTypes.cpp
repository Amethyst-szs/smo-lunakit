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

void PrimitiveTypeHitSensor::render()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    al::HitSensorKeeper* sensorKeeper = mActor->mHitSensorKeeper;
    if (!sensorKeeper)
        return;
    
    for (int i = 0; i < sensorKeeper->mSensorNum; i++) {
        al::HitSensor* curSensor = sensorKeeper->mSensors[i];
        if (!curSensor)
            continue;
        if (!al::isSensorValid(curSensor))
            continue;

        sead::Vector3f sensorTrans = al::getSensorPos(curSensor);
        float sensorRadius = al::getSensorRadius(curSensor);
        const char* sensorName = curSensor->mName;

        if(mSensorTypes & HitSensorType_ATTACK && al::isEqualSubString(sensorName, "Attack")) {
            mColor = {0.f, 0.5f, 0.5f, mOpacity}; // Cyan / Light BLue
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_EYE && (al::isSensorEye(curSensor) || al::isSensorPlayerEye(curSensor))) {
            mColor = {0.f, 0.f, 1.f, mOpacity * 0.85f}; // Blue
            renderer->drawCircle32(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_TRAMPLE && al::isEqualSubString("Trample", sensorName)) {
            mColor = {0.3f, 0.f, 0.75f, mOpacity * 0.5f}; // Deep Purple
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_NPC && al::isSensorNpc(curSensor)) {
            mColor = {0.f, 1.f, 0.f, mOpacity}; // Green
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_BIND && al::isSensorBindableAll(curSensor)) {
            mColor = {0.5f, 0.5f, 0.f, mOpacity}; // Yellow
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_ENEMYBODY && al::isSensorEnemyBody(curSensor)) {
            mColor = {0.9761f, 0.3014f, 0.012f, mOpacity}; // Orange
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_MAPOBJ && al::isSensorMapObj(curSensor)) {
            mColor = {0.8f, 0.05f, 0.5f, mOpacity}; // Pink
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_PLAYERALL && al::isSensorPlayerAll(curSensor)) {
            mColor = {1.f, 0.f, 0.f, mOpacity * 0.3f}; // Red
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_HOLDOBJ && al::isSensorHoldObj(curSensor)) {
            mColor = {0.05f, 0.75f, 0.5f, mOpacity}; // Minty green
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if(mSensorTypes & HitSensorType_MISC) {
            mColor = {0.85f, 0.85f, 0.85f, mOpacity}; // White
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }
    }
}