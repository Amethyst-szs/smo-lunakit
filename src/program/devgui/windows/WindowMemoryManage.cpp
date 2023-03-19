#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowMemoryManage.h"

WindowMemoryManage::WindowMemoryManage(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages) {}

bool WindowMemoryManage::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    ImGui::SetWindowFontScale(1.3f);
    
    ImGui::Checkbox("Simplified Heap Viewer", &mIsSimpleView);

    if(mIsSimpleView)
        drawSimpleHeapView();
    else
        drawComplexHeapTreeItem(sead::HeapMgr::instance()->sRootHeaps[0]);

    ImGui::SetWindowFontScale(mConfig.mFontSize);

    return true;
}

void WindowMemoryManage::drawSimpleHeapView()
{
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

    drawProgressBarPerc(mHeap);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Luna Kit Heap -\nA custom heap containing\nLunaKit and it's features");
    
    drawProgressBarPerc(al::getSequenceHeap());
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Sequence Heap -\nHolds general game info outside\nthe current stage");

    drawProgressBarPerc(al::getSceneHeap());
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Scene Heap -\nHolds current stage memory\n(or any other type of scene)");

    drawProgressBarPerc(al::getSceneResourceHeap());
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- Scene Resource Heap -\nAll resources (archives) requested\nby scene, not world loader");

    drawProgressBarPerc(al::getWorldResourceHeap());
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("- World Resource Heap -\nAll resources requested by the\nWorld List for the current world");
}

void WindowMemoryManage::drawComplexHeapTreeItem(sead::Heap* heap)
{
    ImGui::SetWindowFontScale(1.f);

    bool expanded = ImGui::TreeNode(heap->getName().cstr());

    float mbUsed = (heap->getSize() - heap->getFreeSize()) / 1000000.f;
    float mbSize = heap->getSize() / 1000000.f;
    float percentUsed = (heap->getSize() - heap->getFreeSize()) / (float(heap->getSize()) / 100);

    char buf[32];
    snprintf(buf, sizeof(buf), "%.1fMB/%.1fMB %.0f%%", mbUsed, mbSize, percentUsed);
    ImGui::SameLine();
    ImGui::ProgressBar(percentUsed / 100, ImVec2(-FLT_MIN, 0), buf);

    if (expanded) {
        for (sead::Heap& childRef : heap->mChildren) {
            sead::Heap* child = &childRef;
            if (child)
                drawComplexHeapTreeItem(child);
        }
        ImGui::TreePop();
    }
}

void WindowMemoryManage::drawProgressBarPerc(sead::Heap* heap)
{
    if(!heap) {
        ImGui::TextDisabled("Heap does not exist at this time!");
        return;
    }

    size_t maxSize = heap->getEndAddress() - heap->getStartAddress();
    size_t freeSize = maxSize - heap->getFreeSize();

    float freeSizeF = static_cast<float>(freeSize);
    float maxSizeF = static_cast<float>(maxSize);
    
    float freeSizeMB = freeSizeF / 1000000.f;
    float maxSizeMB = maxSizeF / 1000000.f;

    float percent = freeSizeF / maxSizeF;

    ImGui::BeginGroup();

    char buf[32];
    sprintf(buf, "%.02fMB/%.02fMB %.00f%%", freeSizeMB, maxSizeMB, percent * 100.f);
    
    ImGui::ProgressBar(percent, ImVec2(ImGui::GetWindowWidth() / 1.75f, 0.0f), buf);
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(heap->getName().cstr());

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

    ImGui::ProgressBar(perc, ImVec2(ImGui::GetWindowWidth() / 1.75f, 0.f), buf);
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text(header);

    ImGui::EndGroup();
}