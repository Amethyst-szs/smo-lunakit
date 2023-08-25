#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include "al/util/NerveUtil.h"

#include "sead/basis/seadTypes.h"

namespace NrvFind {
const al::Nerve* getNerveAt(uintptr_t offset);
bool isNerveAt(al::LiveActor* actor, uintptr_t offset);
void setNerveAt(al::LiveActor* actor, uintptr_t offset);
}