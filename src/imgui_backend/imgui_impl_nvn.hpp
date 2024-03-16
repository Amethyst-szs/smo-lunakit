#pragma once

#define IMGUI_USER_CONFIG "imgui_backend/nvn_imgui_config.h"

#include "ImguiShaderCompiler.h"
#include "imgui.h"
#include "nvn/nvn_Cpp.h"
#include "nvn/nvn_CppMethods.h"
#include "nn/types.h"
#include "nn/time.h"
#include "MemoryBuffer.h"

#ifdef __cplusplus

namespace ImguiNvnBackend {

    typedef float Matrix44f[4][4];

    static constexpr int MaxTexDescriptors = 256 + 100;
    static constexpr int MaxSampDescriptors = 256 + 100;

    struct NvnBackendInitInfo {
        nvn::Device *device;
        nvn::Queue *queue;
        nvn::CommandBuffer *cmdBuf;
    };

    struct NvnBackendData {

        // general data

        nvn::Device *device;
        nvn::Queue *queue;
        nvn::CommandBuffer *cmdBuf;

        // builders

        nvn::BufferBuilder bufferBuilder;
        nvn::MemoryPoolBuilder memPoolBuilder;
        nvn::TextureBuilder texBuilder;
        nvn::SamplerBuilder samplerBuilder;

        // shader data

        nvn::Program shaderProgram;

        MemoryBuffer *shaderMemory;
        MemoryBuffer *uniformMemory;

        nvn::ShaderData shaderDatas[2]; // 0 - Vert 1 - Frag

        nvn::VertexStreamState streamState;
        nvn::VertexAttribState attribStates[3];

        // font data

        nvn::TexturePool texPool;
        nvn::SamplerPool samplerPool;

        nvn::MemoryPool sampTexMemPool;

        nvn::MemoryPool fontMemPool;

        int samplerId;
        nvn::Sampler fontSampler;
        int textureId;
        nvn::Texture fontTexture;

        nvn::TextureHandle fontTexHandle;

        // render data

        MemoryBuffer *vtxBuffer;
        MemoryBuffer *idxBuffer;

        // misc data

        nn::TimeSpan lastTick;
        bool isInitialized;

        Matrix44f mProjMatrix = {};

        CompiledData imguiShaderBinary;

        // test shader data

        bool isUseTestShader = false;
        nvn::Program testShader;
        nvn::ShaderData testShaderDatas[2]; // 0 - Vert 1 - Frag
        MemoryBuffer *testShaderBuffer;
        CompiledData testShaderBinary;
    };

    bool createShaders();

    bool setupShaders(u8 *shaderBinary, ulong binarySize);

    bool setupFont();

    void InitBackend(const NvnBackendInitInfo &initInfo);

    void ShutdownBackend();

    void updateInput();

    void updateProjection(ImVec2 dispSize);

    void updateScale(bool isDocked, float dockedScale, float handheldScale);

    void newFrame();

    void setRenderStates();

    void renderDrawData(ImDrawData *drawData);

    NvnBackendData *getBackendData();
}; // namespace ImguiNvnBackend

#endif
