#pragma once

#include "GameFrameWorkNx.h"
#include "GameDrawInfo.h"

namespace al
{
    class SystemKit;
    class AccountHolder;
} // namespace al

class Application {

    SEAD_SINGLETON_DISPOSER(Application)

    public:
        al::SystemKit* mSystemKit; // 0x20
        al::GameFrameworkNx* mFramework; // 0x28
        al::GameDrawInfo *mDrawInfo; // 0x30
        al::AccountHolder *mAccountHolder; // 0x38
};

static_assert(sizeof(Application) == 0x40, "Application Size");

// const Application *Application::sInstance;