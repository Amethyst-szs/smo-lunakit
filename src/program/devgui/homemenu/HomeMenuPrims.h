#pragma once

#include "primitives/PrimitiveQueue.h"
#include "devgui/settings/PrimMenuSettings.h"
#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuPrims : public HomeMenuBase {
public:
    HomeMenuPrims(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenu() override;
    void updateMenuDisplay() override;

private:
    void renderPlayerCategory(al::Scene* scene, PrimitiveQueue* queue);
    void renderTriangleCategory(al::Scene* scene, PrimitiveQueue* queue);
    void renderAreaCategory(al::Scene* scene, PrimitiveQueue* queue);

    void renderHitSensorCategory(al::Scene* scene, PrimitiveQueue* queue);
    const float mMaxDist = 7500.f;

    void drawCategory(PrimMenuCategories cat, const char* catName);

    bool* mIsEnabled = nullptr;
    PrimMenuSettings* mSettings;
};