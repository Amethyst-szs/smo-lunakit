#include "PrimitiveTypes.h"

#include "al/actor/LiveActorKit.h"
#include "helpers/GetHelper.h"
#include "sead/gfx/seadPrimitiveRenderer.h"
#include "al/area/AreaObjGroup.h"
#include "Library/Area/AreaObjDirector.h"
#include "Library/Area/AreaObjUtil.h"
#include "Library/Base/StringUtil.h"
#include "Library/HitSensor/HitSensorKeeper.h"
#include "Project/HitSensor/HitSensor.h"

void PrimitiveTypePoint::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawSphere4x8(mTranslation, mSize, mColor);
}

void PrimitiveTypeLine::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawLine(mPoints[0], mPoints[1], mColor);

    if (mPointsSize[0] > 0.f)
        renderer->drawSphere4x8(mPoints[0], mPointsSize[0], mColor - sead::Color4f(0.f, 0.f, 0.f, 0.25f));
    if (mPointsSize[1] > 0.f)
        renderer->drawSphere4x8(mPoints[1], mPointsSize[1], mColor - sead::Color4f(0.f, 0.f, 0.f, 0.25f));
}

void PrimitiveTypeAxis::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    renderer->drawAxis(mTranslation, mSize);
}

void PrimitiveTypeBox::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    sead::Matrix34f mtx = sead::Matrix34f::ident;
    mtx.setTranslation(mPos);

    renderer->setModelMatrix(mtx);

    sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f::zero, mSize, mFillColor);
    sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f::zero, mSize, mFrameColor);
    renderer->drawCube(shapeAreaSolid);
    renderer->drawWireCube(shapeAreaWire);

    renderer->setModelMatrix(sead::Matrix34f::ident);
}

void PrimitiveTypeArea::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    al::Scene* scene = tryGetScene();

    al::AreaObjGroup* group = scene->mLiveActorKit->mAreaObjDirector->getAreaObjGroup(mGroupName);
    if (!group)
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

        if (al::isEqualString(shapeType, "AreaCubeBase")) {  // origin is at the bottom
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

        if (al::isEqualString(shapeType, "AreaCylinder"))  // origin is at the bottom
            renderer->drawCylinder32(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale.x * 1000, scale.y * 1000, cyl);

        if (al::isEqualString(shapeType, "AreaCylinderCenter"))
            renderer->drawCylinder32(sead::Vector3f(0, 0, 0), scale.x * 1000, scale.y * 1000, cyl);

        if (al::isEqualString(shapeType, "AreaCylinderTop"))
            renderer->drawCylinder32(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale.x * 1000, scale.y * 1000, cyl);
    }

    renderer->setModelMatrix(sead::Matrix34f::ident);
}

void PrimitiveTypeTriangle::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    renderer->drawLine(mTriangle.mPosition1, mTriangle.mPosition2, mColor);
    renderer->drawLine(mTriangle.mPosition2, mTriangle.mPosition3, mColor);
    renderer->drawLine(mTriangle.mPosition3, mTriangle.mPosition1, mColor);

    renderer->drawSphere4x8(mTriangle.mPosition1, 9.f, mColor);
    renderer->drawSphere4x8(mTriangle.mPosition2, 9.f, mColor);
    renderer->drawSphere4x8(mTriangle.mPosition3, 9.f, mColor);
}

void PrimitiveTypeHitSensor::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    al::HitSensorKeeper* sensorKeeper = mActor->mHitSensorKeeper;
    if (!sensorKeeper)
        return;

    for (int i = 0; i < sensorKeeper->mSensorCount; i++) {
        al::HitSensor* curSensor = sensorKeeper->mSensors[i];
        if (!curSensor)
            continue;
        if (!al::isSensorValid(curSensor))
            continue;

        sead::Vector3f sensorTrans = al::getSensorPos(curSensor);
        float sensorRadius = al::getSensorRadius(curSensor);
        const char* sensorName = curSensor->mName;

        if (mSensorTypes & HitSensorType_ATTACK && al::isEqualSubString(sensorName, "Attack")) {
            mColor = {0.f, 0.5f, 0.5f, mOpacity};  // Cyan / Light BLue
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_EYE && (al::isSensorEye(curSensor) || al::isSensorPlayerEye(curSensor))) {
            mColor = {0.f, 0.f, 1.f, mOpacity * 0.85f};  // Blue
            renderer->drawCircle32(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_TRAMPLE && al::isEqualSubString("Trample", sensorName)) {
            mColor = {0.3f, 0.f, 0.75f, mOpacity * 0.5f};  // Deep Purple
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_NPC && al::isSensorNpc(curSensor)) {
            mColor = {0.f, 1.f, 0.f, mOpacity * 0.75f};  // Green
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_BIND && al::isSensorBindableAll(curSensor)) {
            mColor = {0.5f, 0.5f, 0.f, mOpacity};  // Yellow
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_ENEMYBODY && al::isSensorEnemyBody(curSensor)) {
            mColor = {0.9761f, 0.3014f, 0.012f, mOpacity};  // Orange
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_MAPOBJ && al::isSensorMapObj(curSensor)) {
            mColor = {0.8f, 0.05f, 0.5f, mOpacity};  // Pink
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_PLAYERALL && al::isSensorPlayerAll(curSensor)) {
            mColor = {1.f, 0.f, 0.f, mOpacity * 0.3f};  // Red
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_HOLDOBJ && al::isSensorHoldObj(curSensor)) {
            mColor = {0.05f, 0.75f, 0.5f, mOpacity};  // Minty green
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }

        if (mSensorTypes & HitSensorType_MISC) {
            mColor = {0.85f, 0.85f, 0.85f, mOpacity};  // White
            renderer->drawSphere4x8(sensorTrans, sensorRadius, mColor);
            continue;
        }
    }
}

void PrimitiveTypeBezierCurve::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    float percisionRate = 1.f / static_cast<float>(mPercision);
    float rangePoint = 0.f;

    sead::Vector3f startPos;
    sead::Vector3f endPos;

    while (rangePoint <= 1.f) {
        mCurve->calcPos(&startPos, rangePoint);
        rangePoint += percisionRate;
        mCurve->calcPos(&endPos, rangePoint);

        renderer->drawLine(startPos, endPos, mColor);
    }

    mCurve->calcPos(&startPos, 0.f);
    renderer->drawSphere4x8(startPos, 15.f, mColor);

    mCurve->calcPos(&endPos, 1.f);
    renderer->drawSphere4x8(endPos, 15.f, mColor);
}

void PrimitiveTypeRail::render() {
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    float railLength = mRail->getTotalLength();
    float percisionRate = railLength / static_cast<float>(mPercision);
    float rangePoint = 0.f;

    sead::Vector3f startPos;
    sead::Vector3f endPos;

    while (rangePoint <= railLength) {
        mRail->calcPos(&startPos, rangePoint);
        rangePoint += percisionRate;
        mRail->calcPos(&endPos, rangePoint);

        renderer->drawLine(startPos, endPos, mColor);
    }

    mRail->calcPos(&startPos, 0.f);
    renderer->drawSphere4x8(startPos, 20.f, mColor);

    mRail->calcPos(&endPos, railLength);
    renderer->drawSphere4x8(endPos, 20.f, mColor);
}
