#include "WindowBase.h"

#include "devgui/DevGuiManager.h"
#include "devgui/savedata/DevGuiSaveData.h"
#include "devgui/categories/CategoryBase.h"

#include "al/util.hpp"

#include "types.h"

#include "helpers/GetHelper.h"
#include "logger/Logger.hpp"

#include "imgui.h"

WindowBase::WindowBase(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
{
    // Set members from parameters
    mParent = parent;
    mWinName = winName;
    mHeap = mParent->getHeap();
    mIsActive = isActiveByDefault;

    // Prepares up to 8 categories, windows without categories will ignore this
    mCategories.allocBuffer(0x8, mHeap);
    
    // General window flags that all LunaKit windows will share to avoid bugs with the menu bar and anchoring
    mWindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
    mWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

    Logger::log("   Constructing Window: %s\n", winName);
}

void WindowBase::updateWin()
{
    if(!mIsCloseUnpressed) {
        mIsCloseUnpressed = true;
        mIsActive = false;
        mParent->getSaveData()->queueSaveWrite();
    }

    if(!mIsActive)
        return;
        
    if (mCategories.size() > 0) {
        for (int i = 0; i < mCategories.size(); i++) {
            auto* entry = mCategories.at(i);
            entry->updateCat();
        }
    }
}

bool WindowBase::tryUpdateWinDisplay()
{
    ImGui::SetWindowFontScale(1.33f);

    // If this window contains categories, load in the tabs
    if (mCategories.size() > 0) {
        if (ImGui::BeginTabBar("Categories")) {

            for (int i = 0; i < mCategories.size(); i++) {
                auto* entry = mCategories.at(i);

                if (ImGui::BeginTabItem(entry->getCategoryName(), NULL)) {
                    entry->updateCatDisplay();
                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
    }

    return true;
}