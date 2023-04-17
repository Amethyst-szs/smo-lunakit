#pragma once

#include "al/rail/RailRider.h"

namespace al
{

class RailKeeper {
public:
    virtual al::RailRider* getRailRider() const;

    al::RailRider* mRailRider;  // 0x08
};

class IUseRail {
public:
    virtual al::RailRider* getRailRider() const = 0;
};

};