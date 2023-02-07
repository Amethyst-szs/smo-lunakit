#pragma once

#include "al/LiveActor/LiveActor.h"

class CapTargetInfo {
    public:
        CapTargetInfo(void);
        void init(al::LiveActor const*,char const*);
        void setFollowLockOnMtx(char const*,sead::Vector3f const&,sead::Vector3f const&);
        void setLockOnStartAnimName(char const*);
        void setLockOnAnimName(char const*);
        void setHackName(char const*);
        void makeLockOnMtx(sead::Matrix34f *);
        void calcLockOnFollowTargetScale(sead::Vector3f *);

};