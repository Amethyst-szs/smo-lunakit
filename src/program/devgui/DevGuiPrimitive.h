#pragma once

#include "program/GetterUtil.h"

#include "al/collision/alCollisionUtil.h"
#include "al/scene/Scene.h"

#include "game/StageScene/StageScene.h"

#include "heap/seadDisposer.h"
#include <gfx/seadPrimitiveRenderer.h>

struct PrimitivePlayerSettings {
    bool mDrawWorldAxis = true;
    bool mDrawPlayerAxis = true;
    bool mDrawFront = true;
    bool mDrawHackCap = false;
};

struct PrimitiveTriangleSettings {
    bool mDrawTriangle = false;
    bool mDrawComplexTriangle = false;
};

struct PrimitiveAreaSettings {
    bool mDrawAreas = true;

    bool mDrawAreaStage = true;
    bool mDrawAreaDeath = false;
    bool mDrawAreaWater = false;
    bool mDrawArea2D = false;
};

class DevGuiPrimitive {
    SEAD_SINGLETON_DISPOSER(DevGuiPrimitive);
    DevGuiPrimitive();
    ~DevGuiPrimitive();

public:
    void draw(agl::DrawContext* drawContext);
    void drawPlayerCategory();
    void drawColliderCategory();
    void drawAreaCategory();

    bool mIsDrawPrimitives = true;
    PrimitivePlayerSettings mSettingsPlayer;
    PrimitiveTriangleSettings mSettingsTriangle;
    PrimitiveAreaSettings mSettingsArea;

private:
    // Area rendering functions
    void drawAreaGroup(const char* areaName, sead::Color4f wire, sead::Color4f solid);

    // Triangle rendering functions
    void drawSingleTri(al::Triangle* tri);
    void drawTrianglesSimple();
    void drawTrianglesComplex();
};