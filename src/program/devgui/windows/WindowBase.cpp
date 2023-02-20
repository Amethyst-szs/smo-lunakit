#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowBase.h"
#include "devgui/categories/CategoryBase.h"

#include "types.h"

WindowBase::WindowBase(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap)
{
    // Preare PtrArray
    mCategories.allocBuffer(0x10, heap);

    // Set members from parameters
    mWinName = winName;
    mIsActive = active;
    mParent = parent;
    mDevGuiHeap = heap;

    // Default position and size settings
    mConfig.mTrans = ImVec2(0, 19);
    mConfig.mSize = ImVec2(427, 220);
    
    // Window flags
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void WindowBase::updateWin()
{
    if(!mIsCloseUnpressed) {
        mIsCloseUnpressed = true;
        mIsActive = false;
        mParent->refreshAnchor();
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
        
        ImGui::End();
    }

    return true;
}

void WindowBase::setupAnchor(int totalAnchoredWindows, int anchorIdx)
{
    if(totalAnchoredWindows == 0)
        return; // This should never happen, but check just in case to avoid dividing by zero

    WinAnchorType type = mParent->getAnchorType();
    DevGuiWindowConfig* c = &mConfig;

    // Setup window's position based on the anchor type
    switch(type) {
        case WinAnchorType::ANC_TOP:
            c->mTrans = ImVec2(c->mScrSize.x / totalAnchoredWindows * anchorIdx, c->mMinimumY);
            c->mSize = ImVec2(c->mScrSize.x / totalAnchoredWindows, c->mSizeBase.y);
            break;
        case WinAnchorType::ANC_BOTTOM:
            c->mTrans = ImVec2(c->mScrSize.x / totalAnchoredWindows * anchorIdx, c->mScrSize.y - c->mSizeBase.y);
            c->mSize = ImVec2(c->mScrSize.x / totalAnchoredWindows, c->mSizeBase.y);
            break;
        case WinAnchorType::ANC_LEFT:
            c->mTrans = ImVec2(0, (c->mScrSize.y / totalAnchoredWindows * anchorIdx) + c->mMinimumY);
            c->mSize = ImVec2(c->mSizeBase.x, c->mScrSize.y / totalAnchoredWindows);
            break;
        case WinAnchorType::ANC_RIGHT:
            c->mTrans = ImVec2(c->mScrSize.x - c->mSizeBase.x, (c->mScrSize.y / totalAnchoredWindows * anchorIdx) + c->mMinimumY);
            c->mSize = ImVec2(c->mSizeBase.x, c->mScrSize.y / totalAnchoredWindows);
            break;
        default:
            mConfig.mTrans = ImVec2(0, 0);
            mConfig.mSize = ImVec2(1280, 720);
            break;
    }

    c->mSize.x += 1;

    ImGui::SetWindowPos(mConfig.mTrans);
    ImGui::SetWindowSize(mConfig.mSize);
}