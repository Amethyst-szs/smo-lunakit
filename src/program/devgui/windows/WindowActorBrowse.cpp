#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowActorBrowse.h"

WindowActorBrowse::WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    mSelectedActor = nullptr;
}

void WindowActorBrowse::updateWin()
{
    WindowBase::updateWin();

    al::Scene* scene = tryGetScene();
    if(!scene || !mIsActive) {
        mSelectedActor = nullptr;
        return;
    }
    
    return;
}

bool WindowActorBrowse::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    al::Scene* scene = tryGetScene();
    if(!scene)
        return true;
    
    mLineSize = ImGui::GetTextLineHeightWithSpacing();

    drawButtonHeader();
    drawActorList(scene);
    if(mSelectedActor) {
        ImGui::SameLine();
        drawActorInfo();
    }

    return true;
}

void WindowActorBrowse::drawButtonHeader()
{
    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();
    inputChildSize.y = mHeaderSize;
    ImGui::BeginChild("ActorInputs", inputChildSize, false);

    ImGui::SliderInt("Max Chars", &mMaxCharacters, 1, 32);

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorList(al::Scene* scene)
{
    al::LiveActorGroup* group = scene->mLiveActorKit->mLiveActorGroup2;

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if(mSelectedActor)
        listSize.x *= 0.4f;
    listSize.y -= mHeaderSize + 8.f;
    ImGui::BeginChild("ActorList", listSize, true);

    float winWidth = ImGui::GetWindowWidth();
    float winHeight = ImGui::GetWindowHeight();

    float curScrollPos = ImGui::GetScrollY();

    float horizFontSize = ImGui::GetFontSize();
    // int maxCharacters = winWidth / horizFontSize - 4;

    // Render empty space above the current scroll position
    ImGui::Dummy(ImVec2(50, calcRoundedNum(curScrollPos - mLineSize, mLineSize)));

    // Render all actor names and buttons within the range of scroll position -> bottom of window
    for(int i = curScrollPos / mLineSize; i < (curScrollPos + winHeight) / mLineSize; i++) {
        if(i >= group->mActorCount)
            continue;

        al::LiveActor* actor = group->mActors[i];
        char* actorName = getActorName(actor);
        bool isFavorite = false;

        sead::FixedSafeString<0x30> trimName = calcTrimNameFromRight(actorName);
        sead::FormatFixedSafeString<0x9> buttonName("%i", i);

        ImGui::Text(trimName.cstr());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\nTest: %s", actorName, buttonName.cstr());
        if (ImGui::IsItemClicked())
            mSelectedActor = actor;
        
        ImGui::SameLine();

        if(ImGui::RadioButton(buttonName.cstr(), false))
            ImGui::Text("blah");

        free(actorName);
    }

    // Fill in empty space below bottom of window for scroll
    ImGui::Dummy(ImVec2(50, calcRoundedNum((group->mActorCount - (curScrollPos / mLineSize)) * mLineSize, mLineSize)));

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorInfo()
{
    ImVec2 listSize = ImGui::GetContentRegionAvail();
    listSize.y -= mHeaderSize + 8.f;
    ImGui::BeginChild("ActorInfo", listSize, true);
    
    ImGui::Text("Work in progress!");
    if(ImGui::Button("Close"))
        mSelectedActor = nullptr;

    ImGui::EndChild();
}

char* WindowActorBrowse::getActorName(al::LiveActor* actor)
{
    int status;
    char* actName = nullptr;
    actName = abi::__cxa_demangle(typeid(*actor).name(), nullptr, nullptr, &status);
    return actName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::calcTrimNameFromRight(char* text)
{
    int textLen = strlen(text);
    sead::FixedSafeString<0x30> trimName;

    // If string doesn't need trimming, pad to target length and return
    if(textLen <= mMaxCharacters) {
        trimName.append(text);
        trimName.append(' ', mMaxCharacters - textLen);
        return trimName;
    }

    // Create trimed string
    for(int trimIdx = mMaxCharacters; trimIdx >= 0; trimIdx--) {
        trimName.append(&text[textLen - trimIdx - 1], 1);
    }

    trimName.chop(1);
    return trimName;
}

int WindowActorBrowse::calcRoundedNum(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}