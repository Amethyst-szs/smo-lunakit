
#include "ImguiShaderCompiler.h"
#include "fs.h"
#include "helpers.h"
#include "init.h"
#include "glslc/glslc.h"
#include "result.hpp"
#include <cstring>
#include <cstdio>

// list of every shader type nvn supports/glslc can compile (in the order of NVNshaderStage)

const char *shaderNames[] = {
        "VERTEX",
        "FRAGMENT",
        "GEOMETRY",
        "TESS_CONTROL",
        "TESS_EVALUATION",
        "COMPUTE",
};

extern "C" void *glslc_Alloc(size_t size, size_t alignment, void *user_data = nullptr) {
    return nn::init::GetAllocator()->Allocate(ALIGN_UP(size, alignment));
}

extern "C" void glslc_Free(void *ptr, void *user_data = nullptr) {
    nn::init::GetAllocator()->Free(ptr);
}

extern "C" void *glslc_Realloc(void *ptr, size_t size, void *user_data = nullptr) {
    return nn::init::GetAllocator()->Reallocate(ptr, size);
}

void NOINLINE ReadCompiledShader(GLSLCoutput *compileData) {

    for (int i = 0; i < compileData->numSections; ++i) {
        if (compileData->headers[i].genericHeader.common.type != GLSLCsectionTypeEnum::GLSLC_SECTION_TYPE_GPU_CODE)
            continue;
        auto compInfo = &compileData->headers[i].gpuCodeHeader;

    }
}

void createPath(char *fullPath, const char *rootDir, const char *file, const char *ext) {
    sprintf(fullPath, "%s/%s%s", rootDir, file, ext);
}

CompiledData NOINLINE CreateShaderBinary(GLSLCoutput *compileData, const char *shaderName, bool outputFile = true) {

    // TODO: make this work with more/less than 2 shaders

    size_t binarySize = 0;

    for (int i = 0; i < compileData->numSections; ++i) {
        if (compileData->headers[i].genericHeader.common.type == GLSLCsectionTypeEnum::GLSLC_SECTION_TYPE_GPU_CODE) {
            binarySize = ALIGN_UP(binarySize + compileData->headers[i].genericHeader.common.size, 0x100);
        }
    }

    binarySize = ALIGN_UP(binarySize + 0x1000, 0x1000);

    u8 *rawDataBinary = (u8 *) compileData;

    u8 *binaryBuffer = (u8 *) glslc_Alloc(binarySize, 0x1000);
    memset(binaryBuffer, 0, binarySize);

    u32 curBinaryPos = 0x10;
    u32 headerInfo[4] = {};

    // place control sections first (as we dont need to align it)
    for (int i = 0; i < compileData->numSections; ++i) {
        if (compileData->headers[i].genericHeader.common.type != GLSLCsectionTypeEnum::GLSLC_SECTION_TYPE_GPU_CODE)
            continue;

        auto compInfo = &compileData->headers[i].gpuCodeHeader;

        void *controlSection = rawDataBinary + (compInfo->common.dataOffset + compInfo->controlOffset);
        memcpy(binaryBuffer + curBinaryPos, controlSection, compInfo->controlSize);
        headerInfo[i] = curBinaryPos;
        curBinaryPos = ALIGN_UP(curBinaryPos + compInfo->controlSize, 0x100);
    }

    // place data sections next
    for (int i = 0; i < compileData->numSections; ++i) {
        if (compileData->headers[i].genericHeader.common.type != GLSLCsectionTypeEnum::GLSLC_SECTION_TYPE_GPU_CODE)
            continue;
        auto compInfo = &compileData->headers[i].gpuCodeHeader;

        void *dataSection = rawDataBinary + (compInfo->common.dataOffset + compInfo->dataOffset);

        memcpy(binaryBuffer + curBinaryPos, dataSection, compInfo->dataSize);

        headerInfo[compileData->numSections + i] = curBinaryPos;
        curBinaryPos = ALIGN_UP(curBinaryPos + compInfo->dataSize, 0x100);
    }

    memcpy(binaryBuffer, headerInfo, sizeof(headerInfo));

    if (outputFile) {

        char fullPath[0x40] = {};
        createPath(fullPath, "sd:/LunaKit/ImGuiData/", shaderName, ".bin");

        R_ABORT_UNLESS(FsHelper::writeFileToPath(binaryBuffer, binarySize, fullPath))

    }

    return {binaryBuffer, binarySize};

}

const char *GetShaderSource(const char *path) {
    nn::fs::FileHandle handle;

    EXL_ASSERT(FsHelper::isFileExist(path), "Failed to Find File!");

    R_ABORT_UNLESS(nn::fs::OpenFile(&handle, path, nn::fs::OpenMode_Read))

    long size = 0;
    nn::fs::GetFileSize(&size, handle);
    char *sourceFile = (char *) glslc_Alloc(size + 1, 8);

    R_ABORT_UNLESS(nn::fs::ReadFile(handle, 0, sourceFile, size))

    nn::fs::CloseFile(handle);

    sourceFile[size] = '\0';

    return sourceFile;
}

bool ImguiShaderCompiler::CheckIsValidVersion(nvn::Device *device) {
    nn::gfx::detail::GlslcDll *glslcDll = nn::gfx::detail::GlslcDll::GetInstance();

    if (glslcDll->IsInitialized()) {
        auto versionInfo = glslcDll->GlslcGetVersion();
        int minMajorVersion = 0;
        int maxMajorVersion = 0;
        int minMinorVersion = 0;
        int maxMinorVersion = 0;

        device->GetInteger(nvn::DeviceInfo::GLSLC_MIN_SUPPORTED_GPU_CODE_MAJOR_VERSION, &minMajorVersion);
        device->GetInteger(nvn::DeviceInfo::GLSLC_MAX_SUPPORTED_GPU_CODE_MAJOR_VERSION, &maxMajorVersion);
        device->GetInteger(nvn::DeviceInfo::GLSLC_MIN_SUPPORTED_GPU_CODE_MINOR_VERSION, &minMinorVersion);
        device->GetInteger(nvn::DeviceInfo::GLSLC_MAX_SUPPORTED_GPU_CODE_MINOR_VERSION, &maxMinorVersion);

        if ((versionInfo.apiMajor >= minMajorVersion && versionInfo.apiMajor <= maxMajorVersion) &&
            (versionInfo.apiMinor >= minMinorVersion && versionInfo.apiMinor <= maxMinorVersion)) {
            return true;
        } else if (minMajorVersion == 1 && maxMajorVersion == 1) {
            return true;
        }

        return false;


    } else {
        return false;
    }

}

void ImguiShaderCompiler::InitializeCompiler() {

    nn::gfx::detail::GlslcDll *glslcDll = nn::gfx::detail::GlslcDll::GetInstance();

    glslcDll->GlslcSetAllocator(glslc_Alloc, glslc_Free, glslc_Realloc, nullptr);
}

CompiledData ImguiShaderCompiler::CompileShader(const char *shaderName) {

    nn::gfx::detail::GlslcDll *glslcDll = nn::gfx::detail::GlslcDll::GetInstance();

    GLSLCcompileObject initInfo{};
    initInfo.options = glslcDll->GlslcGetDefaultOptions();

    if (!glslcDll->GlslcInitialize(&initInfo)) {
        return {};
    }

    const char *shaders[6];
    NVNshaderStage stages[6];

    char vshPath[0x40] = {}; //"sd:/LunaKit/ImGuiData/sources/imgui_vsh.glsl";
    createPath(vshPath, "sd:/LunaKit/ImGuiData/sources", shaderName, "_vsh.glsl");
    char fshPath[0x40] = {}; //"sd:/LunaKit/ImGuiData/sources/imgui_fsh.glsl";
    createPath(fshPath, "sd:/LunaKit/ImGuiData/sources", shaderName, "_fsh.glsl");

    shaders[0] = GetShaderSource(vshPath);
    stages[0] = NVNshaderStage::NVN_SHADER_STAGE_VERTEX;

    shaders[1] = GetShaderSource(fshPath);
    stages[1] = NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT;

    initInfo.input.sources = shaders;
    initInfo.input.stages = stages;
    initInfo.input.count = 2;

    if (glslcDll->GlslcCompile(&initInfo)) {
    } else {
        EXL_ABORT(0, "Failed to Compile supplied shaders. \nVert Path: %s\nFrag Path: %s\n", vshPath, fshPath);
    }

    glslcDll->Finalize(); // finalize compiler

    // free shader source buffers after compile finishes
    glslc_Free((void *) shaders[0]);
    glslc_Free((void *) shaders[1]);

    return CreateShaderBinary(initInfo.lastCompiledResults->glslcOutput, shaderName, false);

}