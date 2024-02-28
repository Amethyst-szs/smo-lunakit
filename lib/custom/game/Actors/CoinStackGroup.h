#pragma once

#include "Library/LiveActor/LiveActor.h"

struct CoinStack; // stub class 

class CoinStackGroup : public al::LiveActor 
{
    public:
        void setStackAsCollected(CoinStack *stack);
        void generateCoinStackGroup(al::ActorInitInfo const &, int count);
};
