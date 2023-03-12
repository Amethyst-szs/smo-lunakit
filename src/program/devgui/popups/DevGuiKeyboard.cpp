#include "devgui/popups/DevGuiKeyboard.h"

void DevGuiKeyboard::update()
{
    if(!mIsKeyboardOpen)
        return;
    if(!(*mIsKeyboardOpen))
        return;
    
    if(mIsFirstStep) {
        mIsFirstStep = false;
        ImGui::OpenPopup("Keyboard");
    }
    
    ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoResize;

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(.5f, .5f));
    ImGui::SetNextWindowSize(ImVec2(0.f, 0.f), ImGuiCond_Always);

    bool isPopupOpen = ImGui::BeginPopupModal("Keyboard", mIsKeyboardOpen, winFlags);
    if(!isPopupOpen && *mIsKeyboardOpen)
        endKeyboard();

    if(isPopupOpen) {
        ImGui::SetWindowFontScale(2.f);

        if(mBuffer.isEmpty())
            ImGui::TextDisabled("Use keyboard\n");
        else
            ImGui::Text(mBuffer.cstr());

        ImGui::SameLine();
        ImGui::TextDisabled("%i/%u", mBuffer.calcLength(), mMaxCharacters);
        
        switch(mKeyboardType) {
            case DevGuiKeyboardType::KEYTYPE_QWERTY:
                drawQuertyKeyset();
                break;
            case DevGuiKeyboardType::KEYTYPE_NUMBER:
                drawNumberKeyset();
                ImGui::Text("   ");
                ImGui::SameLine();
                drawKeyboardLine("0");
                break;
            case DevGuiKeyboardType::KEYTYPE_IP:
                drawNumberKeyset();
                ImGui::Text("   ");
                ImGui::SameLine();
                drawKeyboardLine("0.");
                break;
        }

        ImGui::EndPopup();
    }
}

bool DevGuiKeyboard::tryOpenKeyboard(uint16_t maxChars, DevGuiKeyboardType keyType, const char** output, bool* isKeyboardOpen)
{
    if(mIsKeyboardOpen && *mIsKeyboardOpen)
        return false;

    mOutputDest = output;
    mIsKeyboardOpen = isKeyboardOpen;

    *mIsKeyboardOpen = true;
    mIsFirstStep = true;
    mIsShift = false;
    mIsCapsLock = false;

    mMaxCharacters = maxChars;
    mBuffer.clear();

    mKeyboardType = keyType;

    return true;
}

void DevGuiKeyboard::endKeyboard()
{
    *mIsKeyboardOpen = false;
    *mOutputDest = mBuffer.cstr();
}

void DevGuiKeyboard::drawQuertyKeyset()
{
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
}

void DevGuiKeyboard::drawNumberKeyset()
{
    drawKeyboardLine("123");
    ImGui::SameLine();
    if(ImGui::Button("<-", ImVec2(88,mKeyLineHeight)))
        mBuffer.chop(1);
    
    drawKeyboardLine("456");
    ImGui::SameLine();
    if(ImGui::Button("Enter", ImVec2(90, mKeyLineHeight)))
        endKeyboard();

    drawKeyboardLine("789");
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
            *mOutputDest = mBuffer.cstr();
            mIsShift = false;
        }

        ImGui::SameLine();
    }

    ImGui::NewLine();
}