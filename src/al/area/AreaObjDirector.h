#pragma once
#include "AreaObjGroup.h"
namespace al
{
    class AreaObjDirector {
        public:
            AreaObjGroup* getAreaObjGroup(const char*) const;
    };

    class IUseAreaObj
    {
    public:
        virtual al::AreaObjDirector* getAreaObjDirector() const = 0;
        
    };
};