#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowMemoryManage.h"

WindowMemoryManage::WindowMemoryManage(DevGuiManager* parent, const char* winName, sead::Heap* heap)
    : WindowBase(parent, winName, heap)
{
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoCollapse;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;
}

bool WindowMemoryManage::tryUpdateWinDisplay()
{
    bool canUpdateDisp = WindowBase::tryUpdateWinDisplay();

    if(!canUpdateDisp)
        return false;

    ImGui::SetWindowFontScale(1.2f);

    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    al::Scene* scene = nullptr;

    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        scene = gameSeq->curScene;
    }

    if(scene) {
        al::LiveActorKit* kit = scene->mLiveActorKit;
        if(kit) {
            al::LiveActorGroup* group = kit->mLiveActorGroup2;
            drawProgressBarFrac(group->mActorCount, group->mMaxActorCount, "Actor Kit");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("- Live Actor Kit -\nTotal actors in scene\nNever changes after scene init");
        } else {
            ImGui::TextDisabled("Live Actor Kit does not exist");
        }
    } else {
        ImGui::TextDisabled("Scene does not exist");
    }

    drawProgressBarPerc(getHeapPercent(mDevGuiHeap), "Station/LK Heap");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Stationed Heap -\nThe earliest existing heap\nLuna Kit is on this heap!");

    drawProgressBarPerc(getHeapPercent(al::getSequenceHeap()), "Sequence Heap");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Sequence Heap -\nHolds general game info outside\nthe current stage");

    drawProgressBarPerc(getHeapPercent(al::getSceneHeap()), "Scene Heap");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Scene Heap -\nHolds current stage memory\n(or any other type of scene)");

    drawProgressBarPerc(getHeapPercent(al::getSceneResourceHeap()), "Scene Res Heap");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Scene Resource Heap -\nAll resources (archives) requested\nby scene, not world loader");

    drawProgressBarPerc(getHeapPercent(al::getWorldResourceHeap()), "World Res Heap");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- World Resource Heap -\nAll resources requested by the\nWorld List for the current world");

    ImGui::SetWindowFontScale(mConfig.mFontSize);

    ImGui::End();

    return true;
}

float WindowMemoryManage::getHeapPercent(sead::Heap* heap)
{
    if(!heap)
        return -1.f;

    size_t freeSize = heap->getFreeSize();
    size_t maxSize = heap->getSize();
    float freeSizeF = static_cast<float>(freeSize);
    float maxSizeF = static_cast<float>(maxSize);

    return freeSizeF / maxSizeF;
}

void WindowMemoryManage::drawProgressBarPerc(float percent, const char* header)
{
    if(percent == -1.f) {
        ImGui::TextDisabled("%s does not currently exist", header);
        return;
    }

    ImGui::BeginGroup();

    char buf[16];
    sprintf(buf, "%.02f%%", percent * 100.f);
    
    ImGui::ProgressBar(percent, ImVec2(0.0f, 0.0f), buf);
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(header);

    ImGui::EndGroup();
}

void WindowMemoryManage::drawProgressBarFrac(int current, int max, const char* header)
{
    float curF = static_cast<float>(current);
    float maxF = static_cast<float>(max);
    float perc = curF / maxF;

    char buf[32];
    sprintf(buf, "%d/%d", current, max);

    ImGui::BeginGroup();

    ImGui::ProgressBar(perc, ImVec2(0.f, 0.f), buf);
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(header);

    ImGui::EndGroup();
}