#include "devgui/DevGuiPrimitive.h"

SEAD_SINGLETON_DISPOSER_IMPL(DevGuiPrimitive)
DevGuiPrimitive::DevGuiPrimitive() = default;
DevGuiPrimitive::~DevGuiPrimitive() = default;

void DevGuiPrimitive::draw(agl::DrawContext* drawContext)
{
    if(!mIsDrawPrimitives)
        return;

    // Get and safety check the StageScene
    al::Scene* curScene = tryGetScene();
    if(!isInScene(curScene) || strstr(typeid(*al::getCurrentNerve(tryGetHakoniwaSequence())).name(), "Destroy"))
        return; // Scene does not exist or is unsafe, return
    
    // Get and check the PlayerActorBase
    PlayerActorBase* player = tryGetPlayerActor(curScene);
    if(!player)
        return;

    // Get all important elements for running the primitive renderer
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    const sead::LookAtCamera* cam = al::getLookAtCamera(curScene, 0);
    const sead::Projection* proj = al::getProjectionSead(curScene, 0);

    // Setup and begin the primitive renderer
    renderer->setDrawContext(drawContext);
    renderer->setCamera(*cam);
    renderer->setProjection(*proj);
    renderer->setModelMatrix(sead::Matrix34f::ident);
    renderer->begin();

    drawPlayerCategory();
    drawColliderCategory();
    drawAreaCategory();

    renderer->end();
}

void DevGuiPrimitive::drawPlayerCategory()
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    PlayerActorBase* player = tryGetPlayerActor();
    if(!player)
        return;

    sead::Vector3f* playerPos = al::getTransPtr(player);

    // Axis Drawing
    if(mSettingsPlayer.mDrawPlayerAxis)
        renderer->drawAxis(*playerPos, 150.f);

    if(mSettingsPlayer.mDrawWorldAxis)
        renderer->drawAxis({0.f, 0.f, 0.f}, 500000.f);
    
    // Drawing the player's front facing direction
    if(mSettingsPlayer.mDrawFront) {
        sead::Vector3f frontTarget;
        al::calcFrontDir(&frontTarget, player);
        frontTarget *= 225.f;
        frontTarget += *playerPos;
        renderer->drawLine(*playerPos, frontTarget, {1.f, 1.f, 1.f, 1.f});
    }

    // Drawing cappy's current position and velocity angle
    if(mSettingsPlayer.mDrawHackCap) {
        PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();
        if(playerHak) {
            // Draw cappy's current position and velocity direction
            sead::Vector3f capPos = al::getTrans(playerHak->mHackCap);
            renderer->drawSphere4x8(capPos, 12.f, {1.f, 0.3f, 0.3f, 0.4f});

            sead::Vector3f capTarget = al::getVelocity(playerHak->mHackCap);
            capTarget *= 20.f;
            capTarget += capPos;
            renderer->drawLine(capPos, capTarget, {0.9f, 0.2f, 0.2f, 1.f});
        }
    }
}

void DevGuiPrimitive::drawColliderCategory()
{
    if(mSettingsTriangle.mDrawTriangle)
        mSettingsTriangle.mDrawComplexTriangle ? drawTrianglesComplex() : drawTrianglesSimple();
}

void DevGuiPrimitive::drawAreaCategory()
{
    if(!mSettingsArea.mDrawAreas)
        return;

    if(mSettingsArea.mDrawAreaStage)
        drawAreaGroup("ChangeStageArea", {0.f, 1.f, 0.2f, 0.85f}, {0.f, 0.8f, 0.f, 0.05f});

    if(mSettingsArea.mDrawAreaDeath)
        drawAreaGroup("DeathArea", {1.f, 0.f, 0.f, 0.8f}, {1.f, 0.2f, 0.f, 0.015f});

    if(mSettingsArea.mDrawAreaWater)
        drawAreaGroup("WaterArea", {0.f, 0.3f, 1.f, 0.85f}, {0.f, 0.f, 0.8f, 0.02f});

    if(mSettingsArea.mDrawArea2D)
        drawAreaGroup("2DMoveArea", {1.f, 1.f, 0.f, 0.75f}, {0.6f, 0.6f, 0.f, 0.01f});
}

void DevGuiPrimitive::drawAreaGroup(const char* areaName, sead::Color4f wire, sead::Color4f solid)
{
    al::Scene* scene = tryGetScene();
    if(!isInScene(scene))
        return;
    
    PlayerActorBase* player = tryGetPlayerActor(scene);
    if(!player)
        return;

    al::AreaObjGroup* group = scene->mLiveActorKit->mAreaObjDirector->getAreaObjGroup(areaName);
    if(group->mCurCount == 0)
        return;

    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();
    
    sead::Color4f cyl = wire;
    cyl.a *= 0.13f;
    
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
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, solid);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, (scale.y / 2 * 1000), 0), scale * 1000.0f, wire);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeCenter")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, 0, 0), scale * 1000.0f, solid);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, 0, 0), scale * 1000.0f, wire);
            renderer->drawCube(shapeAreaSolid);
            renderer->drawWireCube(shapeAreaWire);
        }

        if (al::isEqualString(shapeType, "AreaCubeTop")) {
            sead::PrimitiveDrawer::CubeArg shapeAreaSolid(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, solid);
            sead::PrimitiveDrawer::CubeArg shapeAreaWire(sead::Vector3f(0, -(scale.y / 2 * 1000), 0), scale * 1000.0f, wire);
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

void DevGuiPrimitive::drawSingleTri(al::Triangle* tri)
{
    sead::PrimitiveRenderer* renderer = sead::PrimitiveRenderer::instance();

    renderer->drawLine(tri->mPosition1, tri->mPosition2, {0.f, 0.3f, 1.f, 0.9f});
    renderer->drawLine(tri->mPosition2, tri->mPosition3, {0.f, 0.3f, 1.f, 0.9f});
    renderer->drawLine(tri->mPosition3, tri->mPosition1, {0.f, 0.3f, 1.f, 0.9f});
    
    renderer->drawSphere4x8(tri->mPosition1, 8.f, {0.5f, 0.3f, 1.f, 0.7f});
    renderer->drawSphere4x8(tri->mPosition2, 8.f, {0.5f, 0.3f, 1.f, 0.7f});
    renderer->drawSphere4x8(tri->mPosition3, 8.f, {0.5f, 0.3f, 1.f, 0.7f});
}

void DevGuiPrimitive::drawTrianglesSimple()
{
    PlayerActorBase* playerBase = tryGetPlayerActor();
    if(!playerBase)
        return;
    
    al::Triangle downTri; // Triangle information for below player
    al::Triangle frontTri; // Triangle informaton for in front of player
    
    // Raycast origin
    sead::Vector3f rayOrg = al::getTrans(playerBase);
    rayOrg.y += 30.f;

    // Directional rays
    sead::Vector3f downRay = { 0.f, -500.f, 0.f };

    sead::Vector3f frontRay;
    al::calcFrontDir(&frontRay, playerBase);
    frontRay *= 400.f;

    // Find triangles
    bool isDown = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &downTri, rayOrg, downRay, nullptr, nullptr);
    bool isFront = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &frontTri, rayOrg, frontRay, nullptr, nullptr);

    if(isDown)
        drawSingleTri(&downTri);
    if(isFront)
        drawSingleTri(&frontTri);
}

void DevGuiPrimitive::drawTrianglesComplex()
{
    PlayerActorBase* playerBase = tryGetPlayerActor();
    if(!playerBase)
        return;

    const float checkRange = 450.f;
    const float checkInterval = 50.f;

    sead::Vector3f downRay = { 0.f, -600.f, 0.f };

    sead::Vector3f frontRay;
    al::calcFrontDir(&frontRay, playerBase);
    frontRay *= 600.f;

    sead::Vector3f rightRay = frontRay;
    al::rotateVectorDegreeY(&rightRay, 90.f);

    // Calc downward tris
    for (float xLoop = -checkRange; xLoop < checkRange; xLoop += checkInterval) {
        for (float zLoop = -checkRange; zLoop < checkRange; zLoop += checkInterval) {
            sead::Vector3f origin = al::getTrans(playerBase);
            origin.x += xLoop;
            origin.y += 250.f;
            origin.z += zLoop;

            al::Triangle downTri;
            bool downFind = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &downTri, origin, downRay, nullptr, nullptr);
            if (downFind)
                drawSingleTri(&downTri);
        } // Z loop
    } //X loop

    // Calc front tris
    for (float relLoop = -checkRange; relLoop < checkRange; relLoop += checkInterval) {
        for (float yLoop = -checkRange; yLoop < checkRange; yLoop += checkInterval) {
            sead::Vector3f origin = al::getTrans(playerBase);
            origin += (rightRay * (relLoop / checkRange));
            origin.y += yLoop;

            al::Triangle frontTri;
            bool frontFind = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &frontTri, origin, frontRay, nullptr, nullptr);
            if (frontFind)
                drawSingleTri(&frontTri);
        }
    }
}