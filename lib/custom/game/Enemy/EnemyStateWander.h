#pragma once

#include "al/nerve/ActorStateBase.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/NerveUtil.h"
#include "al/util/RandomUtil.h"

class EnemyStateWander : public al::ActorStateBase {
public:
    EnemyStateWander(al::LiveActor* parent, const char* stateName);
    void appear();

    void exeWait();
    void exeWalk();
    void exeFall();

    bool isWait() const;
    bool isWalk() const;
    bool isFall() const;

    void changeWalkAnim(const char* animName);

    const char* stateName;   // 0x20
    int randNum;             // 0x28
    float walkSpeed;         // 0x2C
    bool isHalfProbability;  // 0x30
};

namespace {
NERVE_HEADER(EnemyStateWander, Wait)
NERVE_HEADER(EnemyStateWander, Walk)
NERVE_HEADER(EnemyStateWander, Fall)
}  // namespace
