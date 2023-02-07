#pragma once

#include "al/collision/Collider.h"

namespace al {
struct Triangle;
};

namespace alCollisionUtil {
bool getFirstPolyOnArrow(al::IUseCollision const*, sead::Vector3f* result, al::Triangle* null, sead::Vector3f const& origin,
    sead::Vector3f const& ray, al::CollisionPartsFilterBase const* nope, al::TriangleFilterBase const* nothanks);

bool getHitPosOnArrow(al::IUseCollision const*, sead::Vector3f*,
    sead::Vector3f const&, sead::Vector3f const&, al::CollisionPartsFilterBase const*, al::TriangleFilterBase const*);
};