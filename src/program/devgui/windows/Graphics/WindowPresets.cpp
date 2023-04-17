#include "WindowPresets.h"

#include "game/GameData/GameDataHolder.h"
#include "game/GameData/GameDataFunction.h"
#include "helpers/GetHelper.h"

#include "devgui/DevGuiHooks.h"
#include "devgui/DevGuiManager.h"

WindowPresets::WindowPresets(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{
    
}

bool WindowPresets::tryUpdateWinDisplay() {
    ImGui::SetWindowFontScale(1.333f);

    auto preset = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();

    preset->mTotalPreset = IM_ARRAYSIZE(presetList);
    preset->mTotalCubemap = IM_ARRAYSIZE(cubemapList);
    preset->mTotalSky = IM_ARRAYSIZE(skyList);

    ImGui::Checkbox("Enabled", &preset->mIsOverride);

    static bool translate = false;
    ImGui::Checkbox("Translate List", &translate);

    ImGui::Checkbox("Override Sky", &preset->mIsOverrideSky);

    bool reload = ImGui::Button("Reload Scene");

    if (translate)
        drawDropdown("Preset", presetList, presetListTranslated, preset->mTotalPreset, &preset->mPreset);
    else
        drawDropdown("Preset", presetList, presetList, preset->mTotalPreset, &preset->mPreset);
    
    if (preset->mIsOverrideSky) drawDropdown("Sky", skyList, skyList, preset->mTotalSky, &preset->mSky);
    drawDropdown("Cubemap", cubemapList, cubemapList, preset->mTotalCubemap, &preset->mCubemap);
    ImGui::SliderInt("Cubemap Scenario", &preset->mScenario, 1, 16);

    if (reload) {
        StageScene* scene = tryGetStageScene();
        if (scene) {
            GameDataHolder* holder = tryGetGameDataHolder();
            ChangeStageInfo stageInfo(holder, "start", GameDataFunction::getCurrentStageName(scene->mHolder), false, -1, ChangeStageInfo::SubScenarioType::UNK);
            GameDataFunction::tryChangeNextStage(scene->mHolder, &stageInfo);
        }
    }
    return true;
}

void WindowPresets::drawDropdown(const char* header, const char* options[], const char* translatedOptions[], const int totalOptions, const char** output)
{
    if(ImGui::BeginCombo(header, *output, mComboFlags)) {
        for(int n = 0; n < totalOptions; n++) {
            bool is_selected = (*output == options[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(translatedOptions[n], is_selected))
                *output = options[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }

        ImGui::EndCombo();
    }
}