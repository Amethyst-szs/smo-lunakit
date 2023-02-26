
#pragma once

#include <basis/seadTypes.h>

class PlayerTrigger {
public:
    enum ECollisionTrigger : u8 {};
    enum EActionTrigger : u8 {};
    void set(PlayerTrigger::ECollisionTrigger type);
    void set(PlayerTrigger::EActionTrigger type);
};