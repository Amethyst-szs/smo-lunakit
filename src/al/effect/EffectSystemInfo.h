#pragma once

namespace nn {
namespace vfx {
class System;
}  // namespace vfx
}  // namespace nn

namespace al {
class EffectSystemInfo {
public:
    s32 field_0;
    nn::vfx::System* mVfxSystem;
    void* field_10;
    s32 field_18;
};
}  // namespace al