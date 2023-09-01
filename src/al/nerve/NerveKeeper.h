#pragma once

#include "Nerve.h"

namespace al {
    class NerveStateCtrl;
    class NerveActionCtrl;

    class NerveKeeper {
    public:
        al::IUseNerve *mParent = nullptr;
        const al::Nerve *mCurrentNerve = nullptr;
        const al::Nerve *mNextNerve = nullptr;
        s32 mStep = 0;
        al::NerveStateCtrl *mStateCtrl = nullptr;
        al::NerveActionCtrl *mActionCtrl = nullptr;

    public:
        NerveKeeper(al::IUseNerve *parent, const al::Nerve *nerve, s32 maxStates);

        NerveKeeper() = default; // custom default ctor

        void initNerveAction(al::NerveActionCtrl *actionCtrl);
        void setNerve(const al::Nerve *nextNerve);
        void tryChangeNerve();
        void update();
        const al::Nerve *getCurrentNerve() const;
        s32 getCurrentStep() const { return mStep; }
        bool isNewNerve() const { return mNextNerve != nullptr; }
        al::NerveStateCtrl *getStateCtrl() const { return mStateCtrl; }
        al::NerveActionCtrl *getActionCtrl() const { return mActionCtrl; }

        template<typename T>
        T *getParent() {
            return static_cast<T *>(mParent);
        }
    };
}