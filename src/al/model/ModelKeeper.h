#pragma once

#include "al/model/ModelCtrl.h"
#include "al/resource/ActorResource.h"

#include "types.h"

namespace al {

class AnimPlayerSkl;
class AnimPlayerSimple;

class ModelKeeper {
public:
    void* vtable;                               //0x00
    const char* mResourceName;                  //0x08
    al::ModelCtrl* mModelCtrl;                  //0x10
    al::ActorResource* mActorRes;               //0x18
    al::AnimPlayerSkl* mAnimPlayerSkl;          //0x20
    al::AnimPlayerSimple* mAnimPlayerSimple1;   //0x28
    al::AnimPlayerSimple* mAnimPlayerSimple2;   //0x30
    al::AnimPlayerSimple* mAnimPlayerSimple3;   //0x38
    al::AnimPlayerSimple* mAnimPlayerSimple4;   //0x40
    al::AnimPlayerSimple* mAnimPlayerSimple5;   //0x48
    al::AnimPlayerSimple* mAnimPlayerSimple6;   //0x50
    void* mUnk;                                 //0x58
    int mUnk2;                                  //0x60

};

} // namespace al