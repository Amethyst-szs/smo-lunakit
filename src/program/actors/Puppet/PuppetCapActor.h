#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"

#include "game/Player/PlayerFunction.h"
#include "game/Player/HackCap/HackCapJointControlKeeper.h"

#include "logger/Logger.hpp"

class PuppetCapActor : public al::LiveActor {
    friend class Ghost;
    public:
        PuppetCapActor(const char *name);
        virtual void init(al::ActorInitInfo const &) override;
        virtual void initAfterPlacement() override;
        virtual void control(void) override;
        virtual void movement(void) override;
        virtual void appear() override;
        virtual void kill() override;

        const char* tryGetPuppetCapName();
        
        void startAction(const char *actName);
        void update();

    private:
        HackCapJointControlKeeper *mJointKeeper;
        al::LiveActor* mModelCap = nullptr;
};
