#include "devgui/DevGuiManager.h"
#include "WindowMemoryManage.h"

#include "al/actor/LiveActorKit.h"
#include "al/util.hpp"

#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"
#include "game/System/Application.h"

#include "imgui.h"

WindowMemoryManage::WindowMemoryManage(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault) {}

bool WindowMemoryManage::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    drawSimpleHeapView();

    ImGui::Separator();

    drawComplexHeapTreeItem(sead::HeapMgr::instance()->sRootHeaps[0]);

    return true;
}

void WindowMemoryManage::drawSimpleHeapView()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    al::Scene* scene = nullptr;

    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        scene = gameSeq->curScene;
    }

    ImGui::SetWindowFontScale(1.2f);

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
    ImGui::SetWindowFontScale(1.1f);

    bool hasNoChildren = heap->mChildren.isEmpty();

    ImGui::BeginGroup();

    // Create a unindented tree node, replacing arrow with bullet if no children exist
    bool expanded = ImGui::TreeNodeEx(heap->getName().cstr(), ImGuiTreeNodeFlags_NoTreePushOnOpen | (hasNoChildren ? ImGuiTreeNodeFlags_Bullet : ImGuiTreeNodeFlags_None));

    float used = (heap->getSize() - heap->getFreeSize());
    float size = heap->getSize();
    float mbUsed = used / 1000000.f;
    float mbSize = size / 1000000.f;

    float percentUsed = (heap->getSize() - heap->getFreeSize()) / (float(heap->getSize()) / 100);

    char buf[32];
    snprintf(buf, sizeof(buf), "%.3f/%.3f MB", mbUsed, mbSize);
    ImGui::SameLine();
    ImGui::ProgressBar(percentUsed / 100, ImVec2(-FLT_MIN, 0), buf);
    ImGui::EndGroup();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("%.0f/%.0f Bytes", used, size);

    if (expanded) {
        for (sead::Heap& childRef : heap->mChildren) {
            sead::Heap* child = &childRef;
            if (child)
                drawComplexHeapTreeItem(child);
        }
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