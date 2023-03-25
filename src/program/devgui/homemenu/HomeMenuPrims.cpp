#include "devgui/homemenu/HomeMenuPrims.h"
#include "devgui/DevGuiManager.h"

HomeMenuPrims::HomeMenuPrims(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{
    mSettings = parent->getPrimitiveSettings();
}

void HomeMenuPrims::updateMenu()
{
    if(!mSettings->getSettingEntryByName("Is Enabled")->isTrue())
        return;
    
    al::Scene* scene = tryGetScene();
    if(!scene)
        return;
    
    PrimitiveQueue* queue = mParent->getPrimitiveQueue();

    renderPlayerCategory(scene, queue);
    renderTriangleCategory(scene, queue);
    renderAreaCategory(scene, queue);
    renderHitSensorCategory(scene, queue);
}

void HomeMenuPrims::updateMenuDisplay()
{
    drawCategory(PrimMenuCat_NONE, nullptr);
    drawCategory(PrimMenuCat_PLAYER, "Player");
    drawCategory(PrimMenuCat_TRIANGLE, "Collision");
    drawCategory(PrimMenuCat_AREA, "Areas");
    drawCategory(PrimMenuCat_HITSENSOR, "Hit Sensors");
}

void HomeMenuPrims::renderPlayerCategory(al::Scene* scene, PrimitiveQueue* queue)
{
    PlayerActorBase* player = tryGetPlayerActor(scene);
    if(!player)
        return;

    sead::Vector3f* playerPos = al::getTransPtr(player);

    if(mSettings->getSettingEntryByName("Player Axis")->isTrue())
        queue->pushAxis(*playerPos, 150.f);

    if(mSettings->getSettingEntryByName("World Axis")->isTrue())
        queue->pushAxis({0.f, 0.f, 0.f}, 500000.f);
    
    // Drawing the player's front facing direction
    if(mSettings->getSettingEntryByName("Player Front")->isTrue()) {
        sead::Vector3f frontTarget;
        al::calcFrontDir(&frontTarget, player);
        frontTarget *= 225.f;
        frontTarget += *playerPos;
        queue->pushLine(*playerPos, frontTarget, {1.f, 1.f, 1.f, 1.f});
    }

    // Drawing cappy's current position and velocity angle
    if(mSettings->getSettingEntryByName("Cappy Info")->isTrue()) {
        PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();
        if(playerHak) {
            // Draw cappy's current position and velocity direction
            sead::Vector3f capPos = al::getTrans(playerHak->mHackCap);
            queue->pushPoint(capPos, 12.f, {1.f, 0.3f, 0.3f, 0.4f});

            sead::Vector3f capTarget = al::getVelocity(playerHak->mHackCap);
            capTarget *= 20.f;
            capTarget += capPos;
            queue->pushLine(capPos, capTarget, {0.9f, 0.2f, 0.2f, 1.f});
        }
    }
}

void HomeMenuPrims::renderTriangleCategory(al::Scene* scene, PrimitiveQueue* queue)
{
    if(mSettings->getSettingEntryByName("Collision")->isTrue()) {
        PlayerActorBase* playerBase = tryGetPlayerActor(scene);
        if(!playerBase)
            return;
        
        al::Triangle downTri; // Triangle information for below player
        al::Triangle frontTri; // Triangle informaton for in front of player
        
        // Raycast origin
        sead::Vector3f rayOrg = al::getTrans(playerBase);
        rayOrg.y += 30.f;

        // Directional rays
        sead::Vector3f downRay = { 0.f, -3000.f, 0.f };

        sead::Vector3f frontRay;
        al::calcFrontDir(&frontRay, playerBase);
        frontRay *= 3000.f;

        // Find triangles
        if(alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &downTri, rayOrg, downRay, nullptr, nullptr))
            queue->pushTriangle(downTri, {1.f, 0.f, 0.f, 1.f});
        if(alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &frontTri, rayOrg, frontRay, nullptr, nullptr))
            queue->pushTriangle(frontTri, {0.f, 1.f, 0.f, 1.f});
    }
}

void HomeMenuPrims::renderAreaCategory(al::Scene* scene, PrimitiveQueue* queue)
{
    if(!mSettings->getSettingEntryByName("Areas")->isTrue())
        return;
    
    if(mSettings->getSettingEntryByName("DeathArea")->isTrue())
        queue->pushArea("DeathArea", {1.f, 0.f, 0.f, 0.8f}, {1.f, 0.2f, 0.f, 0.015f});
    
    if(mSettings->getSettingEntryByName("RecoveryArea")->isTrue())
        queue->pushArea("RecoveryArea", {0.6f, 0.f, 0.f, 0.75f}, {0.6f, 0.1f, 0.f, 0.012f});
    
    if(mSettings->getSettingEntryByName("CameraArea")->isTrue())
        queue->pushArea("CameraArea", {0.7f, 0.7f, 0.7f, 0.65f}, {0.5f, 0.5f, 0.5f, 0.010f});
    
    if(mSettings->getSettingEntryByName("ChangeStageArea")->isTrue())
        queue->pushArea("ChangeStageArea", {0.f, 1.f, 0.2f, 0.85f}, {0.f, 0.8f, 0.f, 0.05f});
    
    if(mSettings->getSettingEntryByName("WarpArea")->isTrue())
        queue->pushArea("WarpArea", {0.2f, 0.4f, 0.1f, 0.80f}, {0.1f, 0.3f, 0.f, 0.03f});
    
    if(mSettings->getSettingEntryByName("WorldEndBorderArea")->isTrue())
        queue->pushArea("WorldEndBorderArea", {0.1f, 0.1f, 0.1f, 0.9f}, {0.1f, 0.1f, 0.1f, 0.f});
    
    if(mSettings->getSettingEntryByName("WaterArea")->isTrue())
        queue->pushArea("WaterArea", {0.f, 0.3f, 1.f, 0.85f}, {0.f, 0.f, 0.8f, 0.02f});
    
    if(mSettings->getSettingEntryByName("2DMoveArea")->isTrue())
        queue->pushArea("2DMoveArea", {1.f, 1.f, 0.f, 0.75f}, {0.6f, 0.6f, 0.f, 0.01f});
    
    if(mSettings->getSettingEntryByName("CameraArea2D")->isTrue())
        queue->pushArea("CameraArea2D", {0.6f, 0.6f, 0.f, 0.65f}, {0.3f, 0.3f, 0.f, 0.005f});
}

void HomeMenuPrims::renderHitSensorCategory(al::Scene* scene, PrimitiveQueue* queue)
{
    if(!mSettings->getSettingEntryByName("Draw Sensors")->isTrue())
        return;

    al::LiveActorGroup* group = scene->mLiveActorKit->mLiveActorGroup2;
    if(!group)
        return;
    
    PlayerActorBase* playerBase = tryGetPlayerActor(scene);
    if(!playerBase)
        return;
    
    int hitSensorTypes = HitSensorRenderTypes::HitSensorType_NONE;

    for(int i = 1; i < mSettings->getTotalSettingsInCat(PrimMenuCat_HITSENSOR); i++) {
        bool isEntryEnabled = mSettings->getSettingEntryInCat(i, PrimMenuCat_HITSENSOR)->isTrue();
        hitSensorTypes |= isEntryEnabled << (i - 1);
    }

    HitSensorRenderTypes hitSensorTypesEnum = (HitSensorRenderTypes)hitSensorTypes;

    for(int i = 0; i < group->mActorCount; i++) {
        al::LiveActor* actor = group->mActors[i];
        if(!actor->mPoseKeeper || !actor->mHitSensorKeeper)
            continue;

        float dist = al::calcDistance(playerBase, actor);

        if(dist < mMaxDist)
            queue->pushHitSensor(actor, hitSensorTypesEnum, (1.f - (dist / mMaxDist)) * 0.45f);
    }
}

void HomeMenuPrims::drawCategory(PrimMenuCategories cat, const char* catName)
{
    if(cat != PrimMenuCat_NONE && !addMenu(catName, true))
        return;
    
    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    bool isDependentValueEnabled = false;

    for(int i = 0; i < mSettings->getTotalSettingsInCat(cat); i++) {
        PrimMenuEntry* entry = mSettings->getSettingEntryInCat(i, cat);

        if(i == 0)
            isDependentValueEnabled = entry->isTrue();

        if(ImGui::MenuItem(entry->getName(), nullptr, entry->isTrue(), !entry->isDependent() || isDependentValueEnabled)) {
            entry->toggleValue();
            mParent->getSaveData()->queueSaveWrite();
        }
    }

    ImGui::PopItemFlag();

    if(cat != PrimMenuCat_NONE)
        ImGui::EndMenu();
}