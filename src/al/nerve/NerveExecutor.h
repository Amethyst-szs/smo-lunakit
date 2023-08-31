#pragma once

#include "Nerve.h"
#include "NerveKeeper.h"

namespace al
{
    class NerveExecutor : public IUseNerve {
    private:
        al::NerveKeeper* mNerveKeeper = nullptr;

    public:
        NerveExecutor(const char* name);
        virtual ~NerveExecutor();
        al::NerveKeeper* getNerveKeeper() const override;
        void initNerve(const al::Nerve* nerve, s32 stateCount);
        void updateNerve();
    };
};