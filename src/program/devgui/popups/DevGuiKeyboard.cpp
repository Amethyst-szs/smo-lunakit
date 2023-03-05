#include "devgui/popups/DevGuiKeyboard.h"

void DevGuiKeyboard::update()
{
    if(!mIsKeyboardOpen)
        return;
    
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(.5f, .5f));
    if(ImGui::BeginPopupModal("Keyboard", NULL)) {
        ImGui::SetWindowFontScale(2.f);

        if(mBuffer.isEmpty())
            ImGui::TextDisabled("Use keyboard\n");
        else
            ImGui::Text(mBuffer.cstr());

        ImGui::SameLine();
        ImGui::TextDisabled("%i/%u", mBuffer.calcLength(), mMaxCharacters);
        
        drawKeyboardLine("123456789-=");
        ImGui::SameLine();
        if(ImGui::Button("<-", ImVec2(88,mKeyLineHeight)))
            mBuffer.chop(1);
        
        ImGui::Text("  ");
        ImGui::SameLine();
        drawKeyboardLine("qwertyuiop");
        
        if(ImGui::Button("Caps", ImVec2(62,mKeyLineHeight)))
            mIsCapsLock = !mIsCapsLock;
        
        ImGui::SameLine();
        drawKeyboardLine("asdfghjkl:");
        ImGui::SameLine();
        if(ImGui::Button("Enter", ImVec2(90, mKeyLineHeight)))
            endKeyboard();

        if(ImGui::Button("Shift", ImVec2(90,mKeyLineHeight)))
            mIsShift = !mIsShift;
        ImGui::SameLine();
        drawKeyboardLine("zxcvbnm,./");

        ImGui::Text("          ");
        ImGui::SameLine();
        if(ImGui::Button("Space", ImVec2(300, mKeyLineHeight)))
            mBuffer.append(" ");
        
        ImGui::EndPopup();
    }
}

bool DevGuiKeyboard::tryOpenKeyboard(uint16_t maxChars, const char* output)
{
    if(mIsKeyboardOpen)
        return false;

    mIsKeyboardOpen = true;
    mIsShift = false;
    mIsCapsLock = false;

    mMaxCharacters = maxChars;
    mBuffer.clear();
    mOutputDest = output;

    ImGui::OpenPopup("Keyboard");
    return true;
}

void DevGuiKeyboard::endKeyboard()
{
    mIsKeyboardOpen = false;
    mOutputDest = mBuffer.cstr();
}

void DevGuiKeyboard::drawKeyboardLine(const char* keys)
{
    int totalKeys = strlen(keys);

    for(int i = 0; i < totalKeys; i++) {
        char keyLabel[] = "X";
        keyLabel[0] = keys[i];

        if(!mIsShift != !mIsCapsLock) {
            int keyNum = (int)keyLabel[0];
            if(keyNum >= 97 && keyNum <= 122)
                keyNum -= 32;
            keyLabel[0] = (char)keyNum;
        }

        if(ImGui::Button(keyLabel, ImVec2(44,mKeyLineHeight)) && mBuffer.calcLength() < mMaxCharacters) {
            mBuffer.append(keyLabel);
            mIsShift = false;
        }

        ImGui::SameLine();
    }

    ImGui::NewLine();
}