#include "WindowPresets.h"

#include "game/GameData/GameDataHolder.h"
#include "game/GameData/GameDataFunction.h"
#include "helpers/GetHelper.h"

#include "devgui/DevGuiHooks.h"
#include "devgui/DevGuiManager.h"

WindowPresets::WindowPresets(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{}

void WindowPresets::updateWin()
{
    WindowBase::updateWin();

    if(!mIsReloadScene)
        return;
    
    StageScene* scene = tryGetStageScene();
    if (!scene) 
        return;

    GameDataHolder* holder = tryGetGameDataHolder(scene);
    ChangeStageInfo stageInfo(holder, "start", GameDataFunction::getCurrentStageName(scene->mGameDataHolder), false, -1, ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(scene->mGameDataHolder, &stageInfo);

    mIsReloadScene = false;
}

bool WindowPresets::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    auto preset = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();

    preset->mTotalPreset = IM_ARRAYSIZE(presetList);
    preset->mTotalCubemap = IM_ARRAYSIZE(cubemapList);
    preset->mTotalSky = IM_ARRAYSIZE(skyList);

    ImGui::Checkbox("Enabled", &preset->mIsOverride);
    ImGui::SameLine();
    if(ImGui::Button("Reload Scene"))
        mIsReloadScene = true;
    
    ImGui::NewLine();

    drawPresetDropdown("Preset", preset->mTotalPreset, &preset->mPreset);

    ImGui::Separator();
    
    drawDropdown("Cubemap", cubemapList, cubemapList, preset->mTotalCubemap, &preset->mCubemap);
    ImGui::SliderInt("Scenario", &preset->mScenario, 1, 15);

    ImGui::Separator();

    ImGui::Checkbox("Override Sky", &preset->mIsOverrideSky);
    if (preset->mIsOverrideSky) drawDropdown("Sky", skyList, skyList, preset->mTotalSky, &preset->mSky);

    return true;
}

void WindowPresets::drawPresetDropdown(const char* header, const int totalOptions, const char** output)
{
    if(ImGui::BeginCombo(header, *output, mComboFlags)) {
        static bool translate = true;
        ImGui::Checkbox("Translate Presets", &translate);

        for(int n = 0; n < totalOptions; n++) {
            bool is_selected = (*output == presetList[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(translate ? presetListTranslated[n] : presetList[n], is_selected))
                *output = presetList[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }

        ImGui::EndCombo();
    }
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