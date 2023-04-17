#include "devgui/DevGuiManager.h"
#include "WindowFPS.h"

#include "game/System/Application.h"
#include "nn/oe.h"

#include "imgui.h"

WindowFPS::WindowFPS(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{
    mWindowFlags |= ImGuiWindowFlags_NoBackground;
    mWindowFlags |= ImGuiWindowFlags_NoNav;
    mWindowFlags |= ImGuiWindowFlags_NoDecoration;
    mWindowFlags |= ImGuiWindowFlags_NoDocking;
}

bool WindowFPS::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;
    
    nn::oe::OperationMode mode = nn::oe::GetOperationMode();
    auto pos = ImVec2(0.f, 690.f);
    if (mode == nn::oe::OperationMode_Docked) pos.y = 870.f;
    ImGui::SetWindowPos(pos);
    ImGui::SetWindowSize(ImVec2(150.f, 30.f));

    float curFPS = Application::instance()->mFramework->calcFps();
    
    if (mRefreshTime == 0.0)
        mRefreshTime = ImGui::GetTime();

    while (mRefreshTime < ImGui::GetTime()) {
        mHistory[mHistoryOffset] = curFPS;
        mHistoryOffset = (mHistoryOffset + 1) % IM_ARRAYSIZE(mHistory);
        mRefreshTime += 1.0f / 5.0f; // 5 FPS
    }

    char overlay[10];
    sprintf(overlay, "%.00f FPS", curFPS);

    ImGui::PlotLines("", mHistory, IM_ARRAYSIZE(mHistory), mHistoryOffset, overlay, 0.0f, 60.0f, ImVec2(140.f, 28.f));

    return true;
}