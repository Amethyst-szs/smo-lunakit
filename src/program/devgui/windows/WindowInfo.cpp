#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    createCategory<CategoryInfScene>("Scene", "Scene Information");
    createCategory<CategoryInfPlayer>("Player", "Player Information");
}