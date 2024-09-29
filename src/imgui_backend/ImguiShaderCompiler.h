#pragma once

#include "nvn/nvn.h"
#include "nvn/nvn_Cpp.h"
#include "nvn/nvn_CppMethods.h"
#include "nn/types.h"

struct CompiledData {
    u8 *ptr;
    ulong size;
};

struct BinaryHeader {

    BinaryHeader(u32* header) {
        mFragmentControlOffset = header[0];
        mVertexControlOffset = header[1];
        mFragmentDataOffset = header[2];
        mVertexDataOffset = header[3];
    }

    u32 mVertexControlOffset;
    u32 mVertexDataOffset;
    u32 mFragmentControlOffset;
    u32 mFragmentDataOffset;

};

namespace ImguiShaderCompiler {
    bool CheckIsValidVersion(nvn::Device *device);
    CompiledData CompileShader(const char *shaderName);
    void InitializeCompiler();
};
