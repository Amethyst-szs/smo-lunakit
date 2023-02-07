#pragma once

#include "../../types.h"

namespace nn::gfx {

    enum class ShaderStage : u8 {
        VERTEX, // total guess for these, taken from nvn headers
        FRAGMENT,
        GEOMETRY,
        TESS_CONTROL,
        TESS_EVALUATION,
        COMPUTE
    };

    class ShaderInfo {
    public:
        void SetDefault(void);
        void SetShaderCodePtr(nn::gfx::ShaderStage,void const*);
        void *GetShaderCodePtr(nn::gfx::ShaderStage);
    };
}