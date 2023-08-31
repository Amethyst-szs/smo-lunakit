#pragma once

#include "lib.hpp"

#include <gfx/seadGraphicsContext.h>
#include <agl/TextureSampler.h>
#include <agl/DevTools.h>

#include "al/graphics/GraphicsPresetDirector.h"

#include "al/LiveActor/LiveActor.h"
#include "al/scene/Scene.h"

#include "al/util/LiveActorUtil.h"
#include <gfx/seadViewport.h>

#include "devgui/DevGuiManager.h"

void exlSetupGraphicsHooks();

void ViewportApplyHook(sead::Viewport *viewport, agl::DrawContext *ctx, agl::RenderBuffer *buffer);
void SkyInitHook(al::LiveActor *actor, al::ActorInitInfo const& info, sead::SafeStringBase<char> const& preset, char const* unk);