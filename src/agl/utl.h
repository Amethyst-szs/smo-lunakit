/**
 * @file GameDataFile.h
 * @brief Utilitis for agl namespace.
 */

#pragma once

#include "../types.h"
#include "DrawContext.h"
#include "math/seadVector.h"
#include "math/seadMatrix.h"
#include "gfx/seadColor.h"

namespace agl {
    class TextureSampler;
    namespace utl {
        class DevTools {
        public:
            void static beginDrawImm(agl::DrawContext *, sead::Matrix34<float> const &, sead::Matrix44<float> const &);

            void static drawTriangleImm(agl::DrawContext *, sead::Vector3<float> const &, sead::Vector3<float> const &,
                                        sead::Vector3<float> const &, sead::Color4f const &);

            void static
            drawLineImm(agl::DrawContext *, sead::Vector3f const &, sead::Vector3<float> const &, sead::Color4f const &,
                        float);

            void static
            drawPointImm(agl::DrawContext *drawCtx, const sead::Vector3f &pos, const sead::Color4f &color, float size);

            void static
            drawCursor(agl::DrawContext *, sead::Vector2f const &screenSize, sead::Vector2f const &pos, float scale);

            void static drawTexture(agl::DrawContext *, const agl::TextureSampler &, const sead::Matrix34f &,
                                    const sead::Matrix44f &, const sead::Color4f &);
        };
    };
};