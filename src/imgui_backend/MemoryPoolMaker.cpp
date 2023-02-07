#include "MemoryPoolMaker.h"
#include "imgui_impl_nvn.hpp"

bool MemoryPoolMaker::createPool(nvn::MemoryPool *result, size_t size,
                                 const nvn::MemoryPoolFlags &flags) {

    auto bd = ImguiNvnBackend::getBackendData();

    void *poolPtr = IM_ALLOC(size);

    nvn::MemoryPoolBuilder memPoolBuilder{};
    memPoolBuilder.SetDefaults().SetDevice(bd->device).SetFlags(
                    flags)
            .SetStorage(poolPtr, size);

    if (!result->Initialize(&memPoolBuilder)) {
        return false;
    }

    return true;
}