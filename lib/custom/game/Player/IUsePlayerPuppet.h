#pragma once

#include <prim/seadSafeString.h>
#include "al/sensor/HitSensor.h"

class IUsePlayerPuppet {
public:
    virtual void start(al::HitSensor*, al::HitSensor*) = 0;
    virtual void end() = 0;
    virtual void cancel() = 0;
    virtual void setTrans(const sead::Vector3f&) = 0;
    virtual void setPose(const sead::Quatf&) = 0;
    virtual void setVelocity(const sead::Vector3f&) = 0;
    virtual void resetPosition(const sead::Vector3f&) = 0;
    virtual sead::Vector3f& getTrans() const = 0;
    virtual sead::Vector3f& getVelocity() const = 0;
    virtual sead::Vector3f& getGravity() const = 0;
    virtual void calcFront(sead::Vector3f*) const = 0;
    virtual void calcUp(sead::Vector3f*) const = 0;
    virtual void startAction(sead::SafeString const&) const = 0;
    virtual bool isActionEnd() const = 0;
    virtual bool isActionPlaying(char const*) const = 0;
    virtual void setAnimRate(float) const = 0;
    virtual int getAnimFrameMax() const = 0;
    virtual void hide() = 0;
    virtual void show() = 0;
    virtual bool isHidden() const = 0;
    virtual void hideSilhouette() = 0;
    virtual void showSilhouette() = 0;
    virtual void hideShadow() = 0;
    virtual void showShadow() = 0;
    virtual void requestDamage() = 0;
    virtual void clearRequestDamage() = 0;
    virtual bool isRequestDamage() const = 0;
    virtual void setBindEndOnGround() = 0;
    virtual bool isBindEndOnGround() const = 0;
    virtual void setBindEndJump(const sead::Vector3f&, int) = 0;
    virtual bool isBindEndJump() const = 0;
    virtual void validateCollisionCheck() = 0;
    virtual void invalidateCollisionCheck() = 0;
    virtual bool isValidCollisionCheck() = 0;
    virtual bool isCollidedGround() = 0;
    virtual sead::Vector3f* getCollidedGroundNormal() = 0;
    virtual void validateSensor() = 0;
    virtual void invalidateSensor() = 0;
};