#pragma once

#include "AreaObj.h"

namespace al
{
    class AreaObjGroup
    {
        public:
            AreaObjGroup(char const*, int);
            void incrementCount();
            void createBuffer();
            void createBuffer(int);
            void registerAreaObj(al::AreaObj *);
            void getAreaObj(int);
            al::AreaObj *getInVolumeAreaObj(sead::Vector3f const &);
            
            const char *mGroupName;
            al::AreaObj **mAreas;
            int mCurCount;
            int mMaxCount;
        
    };
};