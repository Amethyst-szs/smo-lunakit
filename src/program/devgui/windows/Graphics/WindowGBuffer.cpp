#include "WindowGBuffer.h"

#include "game/System/GameDataHolder.h"
#include "game/System/GameDataFunction.h"
#include "helpers.h"

#include "devgui/DevGuiHooks.h"
#include "devgui/DevGuiManager.h"

WindowGBuffer::WindowGBuffer(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{}

bool WindowGBuffer::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    auto gbuffer = DevGuiManager::instance()->getHookSettings()->getGBufferSettings();

    ImGui::Checkbox("Enabled", &gbuffer->mEnable);

    const char* imageTypes[] = { "Base Color", "Normal", "Depth", "Light", "Motion" };
    ImGui::Combo("Buffer Type", &gbuffer->mShowType, imageTypes, 5);

    ImGui::SliderInt("Channel", &gbuffer->mChannel, 0, 5);
    
    return true;
}
