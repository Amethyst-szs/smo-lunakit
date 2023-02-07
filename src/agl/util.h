/**
 * @file util.h
 * @brief Defines enumerators for texture types and formats.
 */

#pragma once

namespace agl
{
    enum TextureType
    {
        TYPELESS = 0,
        UNORM = 1,
        SNORM = 2,
        UFLOAT = 3,
        FLOAT = 4,
        SINT = 5,
        UINT = 6,
        SRGB = 7,
    };
    enum TextureFormat
    {
        INVALID,
        R32_G32_B32_A32,
        R32_G32_B32,
        R16_G16_B16_A16,
        R5_G5_B5_A1,
        R32_G32,
        R32_G8_X24,
        D32_S8_X24,
        R32_X8_X24,
        X32_G8_X24,
        R10_G10_B10_A2,
        R11_G11_B10,
        R8_G8_B8_A8,
        R9_G9B9E5_SHAREDEXP,
        R8_G8_B8_G8,
        R8_G8_B8_X8,
        R4_G4_B4_A4,
        R16_G16,
        R32,
        D32,
        R24_G8,
        D24_S8,
        R24_X8,
        X24_G8,
        R8G8,
        R4_G4,
        R16,
        G8_R8_G8_B8,
        D16,
        D24,
        D24S8,
        D32S8,
        R8,
        A8,
        R1,
        B5_G6_R5,
        A1_B5_G5_R5,
        BC1,
        BC2,
        BC3,
        BC4,
        BC5,
        BC6,
        BC7,
        AYUV,
        Y410,
        Y416,
        NV12,
        P010,
        P016,
        YUY2,
        Y210,
        Y216,
        NV11,
        AI44,
        IA44,
        P8,
        A8P8,
        P208,
        V208,
        V408,
        ASTC4x4,
        ASTC5x4,
        ASTC5x5,
        ASTC6x5,
        ASTC6x6,
        ASTC8x5,
        ASTC8x6,
        ASTC8x8,
        ASTC10x5,
        ASTC10x6,
        ASTC10x8,
        ASTC10x10,
        ASTC12x10,
        ASTC12x12
    };

    enum TextureAttribute
    {

    };

    enum MultiSampleType
    {

    };
};