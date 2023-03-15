#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "al/collision/alCollisionUtil.h"

#include "primitives/PrimitiveQueue.h"
#include "devgui/primsettings/PrimMenuSettings.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuPrims : public HomeMenuBase {
public:
    HomeMenuPrims(DevGuiManager* parent, const char* menuName);

    void updateMenu() override;
    void updateMenuDisplay() override;

private:
    void renderPlayerCategory(al::Scene* scene, PrimitiveQueue* queue);
    void renderTriangleCategory(al::Scene* scene, PrimitiveQueue* queue);
    void renderAreaCategory(al::Scene* scene, PrimitiveQueue* queue);
    void renderHitSensorCategory(al::Scene* scene, PrimitiveQueue* queue);

    void drawCategory(PrimMenuCategories cat, const char* catName);

    bool* mIsEnabled = nullptr;
    PrimMenuSettings* mSettings;
};