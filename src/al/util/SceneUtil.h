#pragma once

#include "gfx/seadFrameBuffer.h"
namespace al {

class ISceneObj;
class Scene;
class IUseSceneObjHolder;
class PlayerHolder;

ISceneObj* getSceneObj(const IUseSceneObjHolder*, int);
PlayerHolder* getScenePlayerHolder(const Scene*);

sead::LogicalFrameBuffer* getSceneFrameBufferMain(al::Scene const*);
float getSceneFrameBufferMainAspect(al::Scene const*);

}  // namespace al
