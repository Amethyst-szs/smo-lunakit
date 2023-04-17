#pragma once

#include "ScreenPointTarget.h"

namespace al
{

class ParameterId;
class ParameterArray;
class ParameterObj;
class ParameterBase;
class ParameterList;

class ScreenPointKeeper {
public:
    uint64_t mTotal;                        // 0x00
    al::ScreenPointTarget** mTargets;       // 0x08
    al::ParameterId* mParamId;              // 0x10
    al::ParameterArray* mParamArray;        // 0x18
    al::ParameterObj* mParamObj;            // 0x20

};

} // namespace al