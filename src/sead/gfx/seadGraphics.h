#ifndef SEAD_GRAPHICS_H_
#define SEAD_GRAPHICS_H_

#ifdef cafe
#include <cafe.h>
#endif // cafe

#ifdef SWITCH
#include <nvn_Cpp.h>
#endif

namespace sead {

    class Graphics
    {
    SEAD_SINGLETON_DISPOSER(Graphics)
    public:
        enum DevicePosture
        {
            cDevicePosture_Same             = 0,
            cDevicePosture_RotateRight      = 1,
            cDevicePosture_RotateLeft       = 2,
            cDevicePosture_RotateHalfAround = 3,
            cDevicePosture_FlipX            = 4,
            cDevicePosture_FlipY            = 5,
            cDevicePosture_FlipXY           = 3,
            cDevicePosture_Invalid          = 4
        };

        // The value for each enumerator in the following enums has been confirmed to be platform-specific
        // when comparing sead between several platforms (3DS, Wii U, Switch)

        enum DepthFunc
        {
#ifdef cafe
            cDepthFunc_Never        = GX2_COMPARE_NEVER,
            cDepthFunc_Less         = GX2_COMPARE_LESS,
            cDepthFunc_Equal        = GX2_COMPARE_EQUAL,
            cDepthFunc_LessEqual    = GX2_COMPARE_LEQUAL,
            cDepthFunc_Greater      = GX2_COMPARE_GREATER,
            cDepthFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
            cDepthFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
            cDepthFunc_Always       = GX2_COMPARE_ALWAYS
#endif // cafe
#ifdef SWITCH
                cDepthFunc_Never        = 0x00000001,
            cDepthFunc_Less         = 0x00000002,
            cDepthFunc_Equal        = 0x00000003,
            cDepthFunc_LessEqual    = 0x00000004,
            cDepthFunc_Greater      = 0x00000005,
            cDepthFunc_NotEqual     = 0x00000006,
            cDepthFunc_GreaterEqual = 0x00000007,
            cDepthFunc_Always       = 0x00000008
#endif // switch
        };

        enum CullingMode
        {
            cCullingMode_Front = 0,
            cCullingMode_Back  = 1,
            cCullingMode_None  = 2,
            cCullingMode_All   = 3
        };

        enum BlendFactor
        {
#ifdef cafe
            cBlendFactor_Zero             = GX2_BLEND_ZERO,
            cBlendFactor_One              = GX2_BLEND_ONE,
            cBlendFactor_SrcColor         = GX2_BLEND_SRC_COLOR,
            cBlendFactor_InvSrcColor      = GX2_BLEND_ONE_MINUS_SRC_COLOR,
            cBlendFactor_SrcAlpha         = GX2_BLEND_SRC_ALPHA,
            cBlendFactor_InvSrcAlpha      = GX2_BLEND_ONE_MINUS_SRC_ALPHA,
            cBlendFactor_DstAlpha         = GX2_BLEND_DST_ALPHA,
            cBlendFactor_InvDstAlpha      = GX2_BLEND_ONE_MINUS_DST_ALPHA,
            cBlendFactor_DstColor         = GX2_BLEND_DST_COLOR,
            cBlendFactor_InvDstColor      = GX2_BLEND_ONE_MINUS_DST_COLOR,
            cBlendFactor_SrcAlphaSaturate = GX2_BLEND_SRC_ALPHA_SATURATE,
            cBlendFactor_ConstantColor    = GX2_BLEND_CONSTANT_COLOR,
            cBlendFactor_InvConstantColor = GX2_BLEND_ONE_MINUS_CONSTANT_COLOR,
            cBlendFactor_ConstantAlpha    = GX2_BLEND_CONSTANT_ALPHA,
            cBlendFactor_InvConstantAlpha = GX2_BLEND_ONE_MINUS_CONSTANT_ALPHA
#endif // cafe
#ifdef SWITCH
                cBlendFactor_Zero             = 0x00000001,
            cBlendFactor_One              = 0x00000002,
            cBlendFactor_SrcColor         = 0x00000003,
            cBlendFactor_InvSrcColor      = 0x00000004,
            cBlendFactor_SrcAlpha         = 0x00000005,
            cBlendFactor_InvSrcAlpha      = 0x00000006,
            cBlendFactor_DstAlpha         = 0x00000007,
            cBlendFactor_InvDstAlpha      = 0x00000008,
            cBlendFactor_DstColor         = 0x00000009,
            cBlendFactor_InvDstColor      = 0x0000000A,
            cBlendFactor_SrcAlphaSaturate = 0x0000000B,
            cBlendFactor_ConstantColor    = 0x00000061,
            cBlendFactor_InvConstantColor = 0x00000062,
            cBlendFactor_ConstantAlpha    = 0x00000063,
            cBlendFactor_InvConstantAlpha = 0x00000064
#endif // switch
        };

        enum BlendEquation
        {
#ifdef cafe
            cBlendEquation_Add        = GX2_BLEND_COMBINE_ADD,
            cBlendEquation_Sub        = GX2_BLEND_COMBINE_SRC_MINUS_DST,
            cBlendEquation_Min        = GX2_BLEND_COMBINE_MIN,
            cBlendEquation_Max        = GX2_BLEND_COMBINE_MAX,
            cBlendEquation_ReverseSub = GX2_BLEND_COMBINE_DST_MINUS_SRC
#endif // cafe
#ifdef SWITCH
                cBlendEquation_Add        = 0x00000001,
            cBlendEquation_Sub        = 0x00000002,
            cBlendEquation_Min        = 0x00000004,
            cBlendEquation_Max        = 0x00000005,
            cBlendEquation_ReverseSub = 0x00000003
#endif // switch
        };

        enum AlphaFunc
        {
#ifdef cafe
            cAlphaFunc_Never        = GX2_COMPARE_NEVER,
            cAlphaFunc_Less         = GX2_COMPARE_LESS,
            cAlphaFunc_Equal        = GX2_COMPARE_EQUAL,
            cAlphaFunc_LessEqual    = GX2_COMPARE_LEQUAL,
            cAlphaFunc_Greater      = GX2_COMPARE_GREATER,
            cAlphaFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
            cAlphaFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
            cAlphaFunc_Always       = GX2_COMPARE_ALWAYS
#endif // cafe
#ifdef SWITCH
                cAlphaFunc_Never        = 0x00000001,
            cAlphaFunc_Less         = 0x00000002,
            cAlphaFunc_Equal        = 0x00000003,
            cAlphaFunc_LessEqual    = 0x00000004,
            cAlphaFunc_Greater      = 0x00000005,
            cAlphaFunc_NotEqual     = 0x00000006,
            cAlphaFunc_GreaterEqual = 0x00000007,
            cAlphaFunc_Always       = 0x00000008
#endif // switch
        };

        enum StencilFunc
        {
#ifdef cafe
            cStencilFunc_Never        = GX2_COMPARE_NEVER,
            cStencilFunc_Less         = GX2_COMPARE_LESS,
            cStencilFunc_Equal        = GX2_COMPARE_EQUAL,
            cStencilFunc_LessEqual    = GX2_COMPARE_LEQUAL,
            cStencilFunc_Greater      = GX2_COMPARE_GREATER,
            cStencilFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
            cStencilFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
            cStencilFunc_Always       = GX2_COMPARE_ALWAYS
#endif // cafe
#ifdef SWITCH
                cStencilFunc_Never        = 0x00000001,
            cStencilFunc_Less         = 0x00000002,
            cStencilFunc_Equal        = 0x00000003,
            cStencilFunc_LessEqual    = 0x00000004,
            cStencilFunc_Greater      = 0x00000005,
            cStencilFunc_NotEqual     = 0x00000006,
            cStencilFunc_GreaterEqual = 0x00000007,
            cStencilFunc_Always       = 0x00000008
#endif // switch
        };

        enum StencilOp
        {
#ifdef cafe
            cStencilOp_Keep          = GX2_STENCIL_KEEP,
            cStencilOp_Zero          = GX2_STENCIL_ZERO,
            cStencilOp_Replace       = GX2_STENCIL_REPLACE,
            cStencilOp_Increment     = GX2_STENCIL_INCR,
            cStencilOp_Decrement     = GX2_STENCIL_DECR,
            cStencilOp_Invert        = GX2_STENCIL_INVERT,
            cStencilOp_IncrementWrap = GX2_STENCIL_INCR_WRAP,
            cStencilOp_DecrementWrap = GX2_STENCIL_DECR_WRAP
#endif // cafe
#ifdef SWITCH
                cStencilOp_Keep          = 0x00000001,
            cStencilOp_Zero          = 0x00000002,
            cStencilOp_Replace       = 0x00000003,
            cStencilOp_Increment     = 0x00000004,
            cStencilOp_Decrement     = 0x00000005,
            cStencilOp_Invert        = 0x00000006,
            cStencilOp_IncrementWrap = 0x00000007,
            cStencilOp_DecrementWrap = 0x00000008
#endif // switch
        };

        enum PolygonMode
        {
#ifdef cafe
            cPolygonMode_Point = GX2_POLYGON_MODE_POINT,
            cPolygonMode_Line  = GX2_POLYGON_MODE_LINE,
            cPolygonMode_Fill  = GX2_POLYGON_MODE_TRIANGLE
#endif // cafe
#ifdef SWITCH
                cPolygonMode_Point = 0x00000000,
            cPolygonMode_Line  = 0x00000001,
            cPolygonMode_Fill  = 0x00000002
#endif // switch
        };
#ifdef SWITCH
        void *unkPtr1; // 0x20
        void *unkPtr2; // 0x28
        nvn::Device* mGfxDevice; // 0x30
        char gap_38[0x20];
        nvn::TexturePool *mTexPool; // 0x58
        char gap_60[0x98];
        int mSamplerId; // 0xF8
        void *unkPtr3; // 0x100
        sead::Atomic<int> mSamplerIdCount; // 0x108
        sead::Atomic<int> mTextureIdCount; // 0x10C
#endif
    };

} // namespace sead

#endif // SEAD_GRAPHICS_H_