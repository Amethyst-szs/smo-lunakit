#pragma once

#include <sead/prim/seadDelegate.h>
#include <sead/math/seadVector.h>

namespace al {
class CollisionParts;
class HitInfo;
class CollisionCheckInfoBase;
class SphereHitResultBuffer;
class ArrowHitResultBuffer;
class DiskHitResultBuffer;
class SphereCheckInfo;
class ArrowCheckInfo;
class DiskCheckInfo;

class ICollisionPartsKeeper {
public:
    virtual void endInit() = 0;
    virtual void addCollisionParts(al::CollisionParts*) = 0;
    virtual void connectToCollisionPartsList(al::CollisionParts*) = 0;
    virtual void disconnectToCollisionPartsList(al::CollisionParts*) = 0;
    virtual void resetToCollisionPartsList(al::CollisionParts*) = 0;
    virtual bool checkStrikePoint(al::HitInfo*, al::CollisionCheckInfoBase*) const = 0;
    virtual bool checkStrikeSphere(al::SphereHitResultBuffer*, al::SphereCheckInfo const&, bool, sead::Vector3f const&) const = 0;
    virtual bool checkStrikeArrow(al::ArrowHitResultBuffer*, al::ArrowCheckInfo const&) const = 0;
    virtual bool checkStrikeSphereForPlayer(al::SphereHitResultBuffer*, al::SphereCheckInfo const&) const = 0;
    virtual bool checkStrikeDisk(al::DiskHitResultBuffer*, al::DiskCheckInfo const&) const = 0;
    virtual void searchWithSphere(al::SphereCheckInfo const&, sead::IDelegate1<al::CollisionParts*>&) const = 0;
    virtual void movement() = 0;
};
}
