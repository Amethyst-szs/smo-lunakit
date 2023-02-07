#pragma once

#include "al/hio/HioNode.h"
#include "sead/math/seadMatrix.h"
#include "sead/math/seadVector.h"

namespace al {
class AreaShape : public HioNode {
public:
    AreaShape(void);
    void setBaseMtxPtr(sead::Matrix34f const*);
    void setScale(sead::Vector3f const&);
    void calcLocalPos(sead::Vector3f *,sead::Vector3f const&);
    void calcWorldPos(sead::Vector3f *,sead::Vector3f const&);
    void calcWorldDir(sead::Vector3f *,sead::Vector3f const&);
    void calcTrans(sead::Vector3f*);

    void *hioNodePtr; // 0x0
    sead::Matrix34f* mBaseMtx; // 0x8
    sead::Vector3f mScale; // = sead::Vector3f::ones; // 0x10

};
}