#include "nerve/util/NerveFindUtil.h"

const al::Nerve* NrvFind::getNerveAt(uintptr_t offset)
{
    return (const al::Nerve*)((((u64)malloc) - 0x00724b94) + offset);
}

bool NrvFind::isNerveAt(al::LiveActor* actor, uintptr_t offset)
{
    const al::Nerve* nerve = getNerveAt(offset);
    return al::isNerve(actor, nerve);
}

void NrvFind::setNerveAt(al::LiveActor* actor, uintptr_t offset)
{
    const al::Nerve* nerve = getNerveAt(offset);
    al::setNerve(actor, nerve);
}

void NrvFind::setNerveAt(StageScene* scene, uintptr_t offset)
{
    const al::Nerve* nerve = getNerveAt(offset);
    al::setNerve(scene, nerve);
}