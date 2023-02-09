#include "program/devgui/categories/CategoryPrimitive.h"

CategoryPrimitive::CategoryPrimitive(const char* catName, const char* catDesc)
    : CategoryBase(catName, catDesc)
{
}

void CategoryPrimitive::updateCatDisplay()
{
    DevGuiPrimitive* prim = DevGuiPrimitive::instance();

    ImGui::Checkbox("Enable Primitive Rendering", &prim->mIsDrawPrimitives);

    if (prim->mIsDrawPrimitives && ImGui::BeginTabBar("Prim Types")) {

        if (ImGui::BeginTabItem("Player")) {
            ImGui::Checkbox("World Axis", &prim->mSettingsPlayer.mDrawWorldAxis);
            ImGui::SameLine();
            ImGui::Checkbox("Player Axis", &prim->mSettingsPlayer.mDrawPlayerAxis);

            ImGui::Checkbox("Facing Direction", &prim->mSettingsPlayer.mDrawFront);

            ImGui::Checkbox("Cap Puppet Info", &prim->mSettingsPlayer.mDrawHackCap);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Colliders")) {
            ImGui::Checkbox("Triangles", &prim->mSettingsTriangle.mDrawTriangle);
            if (prim->mSettingsTriangle.mDrawTriangle) {
                ImGui::SameLine();
                ImGui::Checkbox("Complex (LAG)", &prim->mSettingsTriangle.mDrawComplexTriangle);
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Areas")) {
            ImGui::Checkbox("Areas", &prim->mSettingsArea.mDrawAreas);

            if (prim->mSettingsArea.mDrawAreas) {
                ImGui::Checkbox("Stage", &prim->mSettingsArea.mDrawAreaStage);
                ImGui::SameLine();
                ImGui::Checkbox("Death", &prim->mSettingsArea.mDrawAreaDeath);
                ImGui::SameLine();
                ImGui::Checkbox("Water", &prim->mSettingsArea.mDrawAreaWater);
                ImGui::SameLine();
                ImGui::Checkbox("2D", &prim->mSettingsArea.mDrawArea2D);
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}