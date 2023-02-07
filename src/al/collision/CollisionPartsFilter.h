#pragma once

#include "al/collision/CollisionParts.h"

namespace al {

class CollisionPartsFilterBase {
public:
    virtual bool isInvalidParts(al::CollisionParts const&) const = 0;
};

class CollisionPartsFilterConnectedSensor : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterFunc : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterFuncSendMsg : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterIgnoreOptionalPurpose : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterIgnoreSpecialPurpose : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterMergePair : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterMultiActor : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterOnlySpecialPurpose : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterSpecialPurpose : public al::CollisionPartsFilterBase {

};

class CollisionPartsFilterSubActor : public al::CollisionPartsFilterBase {

};
}
