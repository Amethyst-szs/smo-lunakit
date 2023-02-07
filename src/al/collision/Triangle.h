#pragma once

#include "al/byaml/ByamlIter.h"
#include "math/seadVector.h"

struct CollisionParts;
struct KCPrismData;
struct KCPrismHeader;

namespace al {

class Triangle {
public:
    al::ByamlIter* getAttributes(al::ByamlIter*) const;
    sead::Vector3f getFaceNormal() const;

    CollisionParts* mCollisionParts;
    KCPrismData* mKCPPrismData;
    KCPrismHeader* mKCPrismHeader;

    sead::Vector3f mFaceNormal;
    sead::Vector3f mEdgeNormal1;
    sead::Vector3f mEdgeNormal2;
    sead::Vector3f mEdgeNormal3;
    sead::Vector3f mPosition1;
    sead::Vector3f mPosition2;
    sead::Vector3f mPosition3;
};

} // namespace al