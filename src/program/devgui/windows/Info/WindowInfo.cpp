#include "devgui/DevGuiManager.h"
#include "WindowInfo.h"

#include "program/devgui/categories/info/CategoryInfSequence.h"
#include "program/devgui/categories/info/CategoryInfScene.h"
#include "program/devgui/categories/info/CategoryInfPlayer.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{
    createCategory<CategoryInfSequence>("Sequence", "Sequence Information");
    createCategory<CategoryInfScene>("Scene", "Scene Information");
    createCategory<CategoryInfPlayer>("Player", "Player Information");
}