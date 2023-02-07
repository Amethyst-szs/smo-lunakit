#pragma once

#include "seadFontBase.h"
#include "types.h"

namespace sead {

    struct Heap;
    struct DrawContext;

    class DebugFontMgrNvn : public FontBase {
        SEAD_SINGLETON_DISPOSER(DebugFontMgrNvn)
        public:
            DebugFontMgrNvn();

            void initialize(sead::Heap *, const char *, const char*, unsigned int);
            void initializeFromBinary(sead::Heap *, void *, unsigned long, void *, unsigned long, unsigned int);
            void swapUniformBlockBuffer();

            void begin(sead::DrawContext *) const override;
            void end(sead::DrawContext *) const override;

            float getHeight() const override {
                return 16.f;
            };
            float getWidth() const override {
                return 8.f;
            };
            float getCharWidth(char16_t) const override {
                return 8.f;
            };
            int getMaxDrawNum() const override {
                return 0x80;
            };
            int getEncoding() const override {
                return 2;
            };
            
    };

    class DebugFontMgrJis1Nvn : public FontBase {
        SEAD_SINGLETON_DISPOSER(DebugFontMgrJis1Nvn)
        public:
            DebugFontMgrJis1Nvn();

            void initialize(sead::Heap *, const char *, const char *, const char *, unsigned int);
            void initializeFromBinary(sead::Heap *,void *, ulong,void *, ulong,void const*, uint);
            void swapUniformBlockBuffer();

            void begin(sead::DrawContext *) const override;
            void end(sead::DrawContext *) const override;

            float getHeight() const override {
                return 16.f;
            };
            float getWidth() const override {
                return 8.f;
            };
            float getCharWidth(char16_t val) const override {
                return val < 127u ? 8.0f : 16.0f;
            }
            int getMaxDrawNum() const override {
                return 0x80;
            };
            int getEncoding() const override {
                return 2;
            };
            
    };
}