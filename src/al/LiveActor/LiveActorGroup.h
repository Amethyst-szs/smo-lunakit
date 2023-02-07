#pragma once

#include "al/hio/HioNode.h"

namespace al
{
    class LiveActor;

    class LiveActorGroup : public al::HioNode
    {
    public:
        LiveActorGroup(const char *, int);

        void appearAll();
        void killAll();
        void makeActorAliveAll();
        void makeActorDeadAll();

        bool isExistActor(al::LiveActor const*) const;
        bool isFull() const;

        al::LiveActor* tryFindDeadActor() const;
        int calcAliveActorNum() const;
        
        virtual void registerActor(al::LiveActor *);
        void removeActor(al::LiveActor const*);
        void removeActorAll();

        const char* mGroupName; // _8
        int mMaxActorCount; // _10
        int mActorCount; // _14
        al::LiveActor** mActors; // _18
    };
};