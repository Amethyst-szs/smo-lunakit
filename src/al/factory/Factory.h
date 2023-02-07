#pragma once

#include "types.h"
#include "al/util.hpp"
#include "logger.hpp"

namespace al
{
    template <class T>
    struct NameToCreator
    {
        const char *actorName;
        T createActorFunction;
    };

    template <class T>
    class Factory
    {
    public:
        inline Factory(){};

        virtual const char *convertName(char const *name) const
        {
            return name;
        };

        inline T getCreator(const char *name)
        {
            for (size_t i = 0; i < this->factoryCount; i++)
            {
                if (al::isEqualString(this->actorTable[i].actorName, name))
                {
                    return this->actorTable[i].createActorFunction;
                }
            }
            return nullptr;
        };

    protected:
        // 0x0 is vtable
        const char *factoryName;         // 0x8
        al::NameToCreator<T> *actorTable; // 0x10
        int factoryCount;                // 0x18
    };

} // namespace al
