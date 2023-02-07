#pragma once

#include "agl/DrawContext.h"
#include "gfx/seadCamera.h"
#include "gfx/seadColor.h"
#include "gfx/seadProjection.h"
#include "math/seadMatrix.h"

namespace sead
{
    class FontBase {
    public:
        virtual ~FontBase();
        virtual float getHeight() const;
        virtual float getWidth() const;
        virtual float getCharWidth(char16_t) const;
        virtual int getEncoding() const;
        virtual int getMaxDrawNum() const;
        virtual void begin(sead::DrawContext *) const;
        virtual void end(sead::DrawContext *) const;
        virtual void print(sead::DrawContext *,sead::Projection const&,sead::Camera const&,sead::Matrix34<float> const&,sead::Color4f const&,void const*,int) const;
    };
} // namespace sead
