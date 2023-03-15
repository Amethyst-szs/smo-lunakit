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
        PlayerActorBase* playerBase = tryGetPlayerActor();
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
        bool isDown = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &downTri, rayOrg, downRay, nullptr, nullptr);
        bool isFront = alCollisionUtil::getFirstPolyOnArrow(playerBase, nullptr, &frontTri, rayOrg, frontRay, nullptr, nullptr);

        if(isDown)
            queue->pushTriangle(frontTri, {1.f, 0.f, 0.f, 1.f});
        if(isFront)
            queue->pushTriangle(downTri, {0.f, 1.f, 0.f, 1.f});
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

        if(ImGui::MenuItem(entry->getName(), nullptr, entry->isTrue(), !entry->isDependent() || isDependentValueEnabled))
            entry->toggleValue();
    }

    ImGui::PopItemFlag();

    if(cat != PrimMenuCat_NONE)
        ImGui::EndMenu();
}