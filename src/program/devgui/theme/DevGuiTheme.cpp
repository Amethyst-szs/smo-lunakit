#include "DevGuiTheme.h"
#include "devgui/DevGuiManager.h"

#include "Library/Resource/Resource.h"
#include "al/util.hpp"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/filedevice/seadFileDeviceMgr.h"

#include "nn/fs/fs_files.h"
#include "vapours/results.hpp"
#include "nn/init.h"

#include "helpers/fsHelper.h"

#include "imgui.h"

#include "logger/Logger.hpp"

void DevGuiTheme::init()
{
    Logger::log("Starting theme loader from %s\n", THEMEPATH);

    setupDirectoryInfo();
    mThemes = (al::ByamlIter*)nn::init::GetAllocator()->Allocate(sizeof(al::ByamlIter) * mEntryCount);

    for(int i = 0; i < mEntryCount; i++) {
        Logger::log("   Loading theme %s\n", getFileName(i));
        sead::FormatFixedSafeString<0xff> filePath("%s%s", THEMEPATH, getFileName(i));
        FsHelper::LoadData loadData = { .path = filePath.cstr() };

        FsHelper::loadFileFromPath(loadData);
        mThemes[i] = al::ByamlIter((u8*)loadData.buffer);

        if(mThemes[i].isExistKey("Flags")) {
            al::ByamlIter iterFlags = mThemes[i].getIterByKey("Flags");
            if(iterFlags.isExistKey("DefaultTheme"))
                mThemeIdx = i;
        }
    }

    Logger::log("   Loaded all theme data - Total %i\n", mEntryCount);
}

void DevGuiTheme::tryUpdateTheme()
{
    ImVec2 &dispSize = ImGui::GetIO().DisplaySize;
    bool isDockedMode = !(dispSize.x == 1280 && dispSize.y == 720);

    if (isDockedMode != mIsDocked) {
        mIsDocked = isDockedMode;
        mIsRefreshTheme = true;
    }

    if(!mIsRefreshTheme || !mThemes)
        return;

    ImGuiStyle& style = ImGui::GetStyle();
    
    al::ByamlIter* themeIter = &mThemes[mThemeIdx];

    if(!themeIter->isExistKey("Colors") || !themeIter->isExistKey("Parameters")) {
        Logger::log("Theme does not have a parameter and/or color iter!\n");
        return;
    }

    al::ByamlIter params = themeIter->getIterByKey("Parameters");
    al::ByamlIter colors = themeIter->getIterByKey("Colors");

    setStyleParam(&style.WindowPadding, &params, "WindowPadding");
    setStyleParam(&style.WindowBorderSize, &params, "WindowBorderSize");
    setStyleParam(&style.WindowTitleAlign, &params, "WindowTitleAlign");
    setStyleParam(&style.ChildRounding, &params, "ChildRounding");
    setStyleParam(&style.ChildBorderSize, &params, "ChildBorderSize");
    setStyleParam(&style.PopupRounding, &params, "PopupRounding");
    setStyleParam(&style.PopupBorderSize, &params, "PopupBorderSize");
    setStyleParam(&style.FrameRounding, &params, "FrameRounding");
    setStyleParam(&style.FrameBorderSize, &params, "FrameBorderSize");
    setStyleParam(&style.ScrollbarSize, &params, "ScrollbarSize");
    setStyleParam(&style.ScrollbarRounding, &params, "ScrollbarRounding");
    setStyleParam(&style.GrabMinSize, &params, "GrabMinSize");
    setStyleParam(&style.GrabRounding, &params, "GrabRounding");
    setStyleParam(&style.TabRounding, &params, "TabRounding");
    setStyleParam(&style.TabBorderSize, &params, "TabBorderSize");
    
    ImVec4 BackgroundMain;
    loadColorData(&BackgroundMain, &colors, "BackgroundMain");
    ImVec4 BackgroundPopup;
    loadColorData(&BackgroundPopup, &colors, "BackgroundPopup");
    ImVec4 Text;
    loadColorData(&Text, &colors, "Text");
    ImVec4 TextDisabled;
    loadColorData(&TextDisabled, &colors, "TextDisabled");
    ImVec4 Primary;
    loadColorData(&Primary, &colors, "Primary");
    ImVec4 PrimaryHover;
    loadColorData(&PrimaryHover, &colors, "PrimaryHover");
    ImVec4 PrimaryInteract;
    loadColorData(&PrimaryInteract, &colors, "PrimaryInteract");
    ImVec4 Highlight;
    loadColorData(&Highlight, &colors, "Highlight");
    ImVec4 HighlightInteract;
    loadColorData(&HighlightInteract, &colors, "HighlightInteract");

    style.Colors[ImGuiCol_Text]              = Text;
    style.Colors[ImGuiCol_TextDisabled]      = TextDisabled;

    style.Colors[ImGuiCol_WindowBg]          = BackgroundMain;
    style.Colors[ImGuiCol_ChildBg]           = BackgroundMain;
    style.Colors[ImGuiCol_PopupBg]           = BackgroundPopup;

    style.Colors[ImGuiCol_Border]            = PrimaryInteract;
    style.Colors[ImGuiCol_BorderShadow]      = PrimaryHover;

    style.Colors[ImGuiCol_FrameBg]           = Primary;
    style.Colors[ImGuiCol_FrameBgHovered]    = PrimaryHover;
    style.Colors[ImGuiCol_FrameBgActive]     = PrimaryInteract;

    style.Colors[ImGuiCol_TitleBg]           = Primary;
    style.Colors[ImGuiCol_TitleBgActive]     = PrimaryHover;
    style.Colors[ImGuiCol_TitleBgCollapsed]  = BackgroundMain;

    style.Colors[ImGuiCol_MenuBarBg]         = Primary;

    style.Colors[ImGuiCol_ScrollbarBg]       = Primary;
    style.Colors[ImGuiCol_ScrollbarGrab]     = PrimaryHover;
    style.Colors[ImGuiCol_ScrollbarGrabHovered]= Highlight;
    style.Colors[ImGuiCol_ScrollbarGrabActive]= HighlightInteract;

    style.Colors[ImGuiCol_CheckMark]         = HighlightInteract;

    style.Colors[ImGuiCol_SliderGrab]        = PrimaryInteract;
    style.Colors[ImGuiCol_SliderGrabActive]  = HighlightInteract;

    style.Colors[ImGuiCol_Button]            = PrimaryHover;
    style.Colors[ImGuiCol_ButtonHovered]     = Highlight;
    style.Colors[ImGuiCol_ButtonActive]      = HighlightInteract;

    style.Colors[ImGuiCol_Header]            = Primary;
    style.Colors[ImGuiCol_HeaderHovered]     = PrimaryHover;
    style.Colors[ImGuiCol_HeaderActive]      = HighlightInteract;

    style.Colors[ImGuiCol_Separator]         = PrimaryHover;
    style.Colors[ImGuiCol_SeparatorHovered]  = PrimaryInteract;
    style.Colors[ImGuiCol_SeparatorActive]   = HighlightInteract;

    style.Colors[ImGuiCol_ResizeGrip]        = PrimaryHover;
    style.Colors[ImGuiCol_ResizeGripHovered] = Highlight;
    style.Colors[ImGuiCol_ResizeGripActive]  = HighlightInteract;

    style.Colors[ImGuiCol_Tab]               = Primary;
    style.Colors[ImGuiCol_TabHovered]        = Highlight;
    style.Colors[ImGuiCol_TabActive]         = PrimaryHover;
    style.Colors[ImGuiCol_TabUnfocused]      = BackgroundPopup;
    style.Colors[ImGuiCol_TabUnfocusedActive]= BackgroundMain;

    style.Colors[ImGuiCol_DockingPreview]    = Highlight;
    style.Colors[ImGuiCol_DockingEmptyBg]    = PrimaryHover;

    style.Colors[ImGuiCol_PlotLines]         = Highlight;
    style.Colors[ImGuiCol_PlotLinesHovered]  = HighlightInteract;

    style.Colors[ImGuiCol_PlotHistogram]     = Highlight;
    style.Colors[ImGuiCol_PlotHistogramHovered]= Highlight;

    style.Colors[ImGuiCol_ModalWindowDimBg]  = ImVec4(BackgroundMain.x, BackgroundMain.y, BackgroundMain.z, 0.9f);

    mIsRefreshTheme = false;
    Logger::log("Setup LunaKit theme: %s\n", getThemeName());
}

const char* DevGuiTheme::getThemeName()
{
    const char* val;
    if(!mThemes[mThemeIdx].tryGetStringByKey(&val, "ThemeName"))
        return "Name Missing!";

    return val;
}

const char* DevGuiTheme::getThemeName(int idx)
{
    const char* val;
    if(!mThemes[idx].tryGetStringByKey(&val, "ThemeName"))
        return "Name Missing!";

    return val;
}

void DevGuiTheme::setWinThemeByName(const char* themeName)
{
    for(int i = 0; i < mEntryCount; i++) {
        const char* compareName;
        if(!mThemes[i].tryGetStringByKey(&compareName, "ThemeName"))
            continue;

        if(!al::isEqualString(themeName, compareName))
            continue;

        mIsRefreshTheme = true;
        mThemeIdx = i;
        return;
    }
}

void DevGuiTheme::loadColorData(ImVec4* result, al::ByamlIter* colors, const char* colorName)
{
    if(!colors->isExistKey(colorName)) {
        Logger::log("Theme color value %s is missing!\n", colorName);
        return;
    }

    al::ByamlIter data = colors->getIterByKey(colorName);
    
    data.tryGetFloatByKey(&result->x, "R");
    data.tryGetFloatByKey(&result->y, "G");
    data.tryGetFloatByKey(&result->z, "B");
    data.tryGetFloatByKey(&result->w, "A");
}

void DevGuiTheme::setStyleParam(bool* target, al::ByamlIter* parameters, const char* parameterName)
{
    if(!parameters->tryGetBoolByKey(target, parameterName))
        Logger::log("Failed to find parameter %s in theme\n", parameterName);
}

void DevGuiTheme::setStyleParam(float* target, al::ByamlIter* parameters, const char* parameterName)
{
    if(!parameters->tryGetFloatByKey(target, parameterName))
        Logger::log("Failed to find parameter %s in theme\n", parameterName);
}

void DevGuiTheme::setStyleParam(ImVec2* target, al::ByamlIter* parameters, const char* parameterName)
{
    if(!parameters->isExistKey(parameterName)) {
        Logger::log("Failed to find parameter %s in theme!\n", parameterName);
        return;
    }

    al::ByamlIter data = parameters->getIterByKey(parameterName);

    data.tryGetFloatByKey(&target->x, "X");
    data.tryGetFloatByKey(&target->y, "Y");
}

void DevGuiTheme::setupDirectoryInfo()
{
    nn::fs::DirectoryHandle handle;
    nn::Result r = nn::fs::OpenDirectory(&handle, "sd:/LunaKit/LKData/Themes/", nn::fs::OpenDirectoryMode_File);
    if (r.IsFailure()) return;
    s64 entryCount;
    r = nn::fs::GetDirectoryEntryCount(&entryCount, handle);
    if (r.IsFailure()) {
        nn::fs::CloseDirectory(handle);
        return;
    }
    nn::fs::DirectoryEntry* entryBuffer = (nn::fs::DirectoryEntry*)nn::init::GetAllocator()->Allocate(sizeof(nn::fs::DirectoryEntry) * entryCount);
    r = nn::fs::ReadDirectory(&entryCount, entryBuffer, handle, entryCount);
    nn::fs::CloseDirectory(handle);
    if (r.IsFailure()) {
        delete[] entryBuffer;
        return;
    }
    delete[] mEntries;
    mEntries = entryBuffer;
    mEntryCount = entryCount;
}
