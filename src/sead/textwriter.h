/**
 * @file viewport.h
 * @brief Basic Viewport class.
 */

#pragma once

#include "../types.h"
#include <sead/gfx/seadDrawContext.h>
#include <sead/gfx/seadProjection.h>
#include <sead/math/seadBoundBox.h>
#include <sead/gfx/seadCamera.h>
#include <sead/gfx/seadViewport.h>
#include <sead/devenv/seadDebugFontMgrNvn.h>
#include <sead/devenv/seadFontBase.h>
#include <sead/gfx/seadColor.h>

namespace sead
{
    class TextWriter
    {
        public:
            virtual ~TextWriter();

            TextWriter(sead::DrawContext *);
            TextWriter(sead::DrawContext *, sead::Viewport const *);

            void printImpl_(char const*, int, bool, sead::BoundBox2<float>*);
            void printf(char const*, ...);
            void printf(char16_t const*, ...);
            void setScaleFromFontHeight(float);
            void setCursorFromTopLeft(sead::Vector2<f32> const &);
            void beginDraw();
            void endDraw();
            sead::DebugFontMgrNvn *getDefaultFont();
            static void setDefaultFont(sead::FontBase *);
            static void setupGraphics(sead::DrawContext*);


            sead::Viewport *mViewport;
            sead::Projection *mProjection;
            sead::Camera *mCamera;
            int TextWriter_x20;
            int TextWriter_x24;
            int TextWriter_x28;
            int TextWriter_x2C;
            sead::Vector2<float> mScale;
            sead::Color4f mColor;
            int TextWriter_x48;
            float mLineSpace;
            sead::BoundBox2<float> *mBoundBox2;
            int TextWriter_x58;
            int TextWriter_x5C;
            char16_t *mFormatBuffer;
            int mFormatBufferSize;
            int TextWriter_x6C;
            sead::DrawContext *mDrawContext;
    };
};