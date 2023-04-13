#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include "al/util/NerveUtil.h"

namespace NrvFindHelper {
const al::Nerve* getNerveAt(uintptr_t offset);
bool isNerveAt(al::LiveActor* actor, uintptr_t offset);
void setNerveAt(al::LiveActor* actor, uintptr_t offset);
}