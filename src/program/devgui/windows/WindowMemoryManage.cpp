#include "program/devgui/windows/WindowMemoryManage.h"

WindowMemoryManage::WindowMemoryManage(const char* winName, sead::Heap* heap)
    : WindowBase(winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(0, 19);
    mConfig.mSize = ImVec2(427, 220);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoCollapse;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;
}

void WindowMemoryManage::updateWinDisplay()
{
    WindowBase::updateWinDisplay();

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
        } else {
            ImGui::TextDisabled("Live Actor Kit does not exist");
        }
    } else {
        ImGui::TextDisabled("Scene does not exist");
    }

    drawProgressBarPerc(getHeapPercent(mDevGuiHeap), "Station/LK Heap");
    drawProgressBarPerc(getHeapPercent(al::getSequenceHeap()), "Sequence Heap");
    drawProgressBarPerc(getHeapPercent(al::getSceneHeap()), "Scene Heap");
    drawProgressBarPerc(getHeapPercent(al::getSceneResourceHeap()), "Scene Res Heap");
    drawProgressBarPerc(getHeapPercent(al::getWorldResourceHeap()), "World Res Heap");

    ImGui::SetWindowFontScale(mConfig.mFontSize);

    ImGui::End();
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

    ImGui::ProgressBar(percent, ImVec2(0.0f, 0.0f));
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(header);
}

void WindowMemoryManage::drawProgressBarFrac(int current, int max, const char* header)
{
    float curF = static_cast<float>(current);
    float maxF = static_cast<float>(max);
    float perc = curF / maxF;

    char buf[32];
    sprintf(buf, "%d/%d", current, max);

    ImGui::ProgressBar(perc, ImVec2(0.f, 0.f), buf);
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(header);
}

void WindowMemoryManage::configImGuiStyle()
{
    WindowBase::configImGuiStyle();
}