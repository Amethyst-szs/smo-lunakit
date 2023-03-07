#pragma once

#include "Nerve.h"

namespace al
{
    class NerveStateCtrl;
    class NerveActionCtrl;

    class NerveKeeper
    {
    public:
        NerveKeeper(al::IUseNerve *, const al::Nerve *, int);

        void initNerveAction(al::NerveActionCtrl*);

        void update();

        void tryChangeNerve();
        void setNerve(const al::Nerve *);
        al::Nerve* getCurrentNerve() const;

        al::IUseNerve* mParent;             // 0x00
        const al::Nerve* mPrevNrv;          // 0x08
        const al::Nerve* mNrv;              // 0x10
        int mStep;                          // 0x18
        int padding;                        // 0x1c
        al::NerveStateCtrl* mStateCtrl;     // 0x20
        al::NerveActionCtrl* mActionCtrl;   // 0x28
    };
};