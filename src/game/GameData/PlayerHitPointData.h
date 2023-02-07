#pragma once

#include "game/Interfaces/ByamlSave.h"
#include "types.h"

class PlayerHitPointData : public ByamlSave {
public:
    PlayerHitPointData(void);
    void write(al::ByamlWriter *) override;
    void read(al::ByamlIter const&) override;

    void setKidsModeFlag(bool);
    void init(void);
    void recoverMax(void);
    int getCurrent(void) const;
    int getMaxCurrent(void) const;
    int getMaxWithItem(void) const;
    int getMaxWithoutItem(void) const;
    bool isMaxCurrent(void) const;
    bool isMaxWithItem(void) const;
    void getMaxUpItem(void);
    void recover(void);
    void recoverForDebug(void);
    void damage(void);
    void kill(void);
    void forceNormalMode(void);
    void endForceNormalMode(void);
    bool isForceNormalMode(void) const;

    bool mIsKidsMode; // 0x8
    int mCurrentHit; // 0xC
    bool mIsHaveMaxUpItem; // 0x10
    bool mIsForceNormalHealth; // 0x11
};