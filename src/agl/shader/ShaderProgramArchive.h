/**
 * @file ShaderProgramArchive.h
 * @brief Defines a class wrapper for SHARCB (Shader Binary) archives.
 */

#pragma once

#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>

namespace agl
{
    class ResBinaryShaderArchive;
    class ResShaderArchive;
    class ResShaderProgram;
    class ResShaderSource;

    class ShaderProgramArchive : public sead::IDisposer, public sead::hostio::Node
    {
    public:
        ShaderProgramArchive();

        virtual ~ShaderProgramArchive();

        void destroy();
        void createWithOption(agl::ResBinaryShaderArchive, agl::ResShaderArchive, u32, sead::Heap *);
        void destroyResFile_();
        void initialize(agl::ShaderProgramArchive *, s32, agl::ResShaderProgram, sead::Heap *);
        void updateCompileInfo();
        void setUp();
        void setUp_(bool);

        agl::ResBinaryShaderArchive* mBinaryShaderArchive; // _28
        agl::ResShaderArchive* mResShaderArchive;          // _30
        u8 _38[0xB8-0x30];
        
    };
};