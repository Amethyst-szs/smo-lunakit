#include "NrvFindHelper.h"

const al::Nerve* NrvFindHelper::getNerveAt(uintptr_t offset)
{
    return (const al::Nerve*)((((u64)malloc) - 0x00724b94) + offset);
}

bool NrvFindHelper::isNerveAt(al::LiveActor* actor, uintptr_t offset)
{
    const al::Nerve* nerve = getNerveAt(offset);
    return al::isNerve(actor, nerve);
}

void NrvFindHelper::setNerveAt(al::LiveActor* actor, uintptr_t offset)
{
    const al::Nerve* nerve = getNerveAt(offset);
    al::setNerve(actor, nerve);
}