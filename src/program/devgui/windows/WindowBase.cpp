#include "devgui/DevGuiManager.h"
#include "devgui/categories/CategoryBase.h"

#include "types.h"

#include "WindowBase.h"

WindowBase::WindowBase(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
{
    // Set members from parameters
    mParent = parent;
    mWinName = winName;
    mHeap = mParent->getHeap();
    mIsActive = isActiveByDefault;

    // Prepares up to 8 categories, windows without categories will ignore this
    mCategories.allocBuffer(0x8, mHeap);
    
    // General window flags that all LunaKit windows will share to avoid bugs with the menu bar and anchoring
    mConfig.mWindowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

    Logger::log("Constructing Window: %s (Is Anchored: %s)\n", winName, BTOC(isAnchor));
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
    ImGui::SetWindowFontScale(mConfig.mFontSize);

    // If this window contains categories, load in the tabs
    if (mCategories.size() > 0) {
        if (ImGui::BeginTabBar("Categories", mConfig.mTabFlags)) {

            for (int i = 0; i < mCategories.size(); i++) {
                auto* entry = mCategories.at(i);

                if (ImGui::BeginTabItem(entry->getCategoryName(), NULL, mConfig.mTabItemFlags)) {
                    entry->updateCatDisplay();
                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
    }

    return true;
}

void WindowBase::setupAnchor(int totalAnchoredWindows, int anchorIdx)
{
    return;
}