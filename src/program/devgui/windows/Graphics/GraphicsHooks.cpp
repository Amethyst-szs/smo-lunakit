#include "devgui/DevGuiHooks.h"
#include "GraphicsHooks.h"

namespace al {
    class GraphicsSystemInfo;
}

HOOK_DEFINE_TRAMPOLINE(CubeMapSetter) {
    static void Callback(al::GraphicsSystemInfo *i, al::Resource const*r, char const*a, char const*b) {
        a = "SandWorldHomeStage";
        Orig(i, r, a, b);
        svcOutputDebugString(a, 0x50);
    }
};

HOOK_DEFINE_TRAMPOLINE(InitGraphicsInfoHook) {
    static void Callback(al::Scene *scene, char const *stage, int scenario) {
        auto presets = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();
        
        if (presets->mIsOverride) {
            scenario = presets->mScenario;
        }

        Orig(scene, stage, scenario);
    }
};

HOOK_DEFINE_TRAMPOLINE(RegisterPresetHook) {
    static void Callback(al::GraphicsPresetDirector *presetDirector, char const* preset, char const* cubemap_location, char const* file, bool d) {
        auto presets = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();
        
        if (presets->mIsOverride) {
            preset = presets->mPreset;
            file = presets->mCubemap;
            cubemap_location = "Default";
        }

        Orig(presetDirector, preset, cubemap_location, file, d);
    }
};

HOOK_DEFINE_TRAMPOLINE(RequestPresetHook) {
    static void Callback(al::GraphicsPresetDirector *presetDirector, char const* preset, int b, int c, int d, sead::Vector3<float> const& rot) {
        auto presets = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();
        
        if (presets->mIsOverride) {
            preset = presets->mPreset;
            b = 1000;
            c = 0;
            d = 0;
        }

        Orig(presetDirector, preset, b, c, d, rot);
    }
};

HOOK_DEFINE_TRAMPOLINE(RequestCubeMapHook) {
    static void Callback(void *cubeMapKeeper, int a, char const* location, char const* file) {
        auto presets = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();
        
        if (presets->mIsOverride) {
            a = 1000;
            location = "Default";
            file = presets->mCubemap;
        }

        Orig(cubeMapKeeper, a, location, file);
    }
};

void SkyInitHook(al::LiveActor *actor, al::ActorInitInfo const& info, sead::SafeStringBase<char> const& preset, char const* unk) {
    auto presets = DevGuiManager::instance()->getHookSettings()->getGraphicsPresetSettings();
    
    if (presets->mIsOverride && presets->mIsOverrideSky) {
        return al::initActorWithArchiveName(actor, info, presets->mSky, unk);
    }
    al::initActorWithArchiveName(actor, info, preset, unk);
}

void ViewportApplyHook(sead::Viewport *viewport, agl::DrawContext *ctx, agl::RenderBuffer *buffer) {
    auto gbuffer = DevGuiManager::instance()->getHookSettings()->getGBufferSettings();
    
    if (gbuffer->mBuffer && gbuffer->mEnable) {
        auto b = gbuffer->mBuffer;
        agl::TextureData *apply = b->mGBufBaseColor;

        switch (gbuffer->mShowType) {
            case 0: // Base Color
                apply = b->mGBufBaseColor;
                break;
            case 1: // Normal
                apply = b->mGBufNrmWorld;
                break;
            case 2: // Depth
                apply = b->mGBufDepthView;
                break;
            case 3: // Light
                apply = b->mGBufLightBuffer;
                break;
            case 4: // Motion
                apply = b->mGBufMotionVec;
                break;
        }

        sead::GraphicsContext context;
        context.apply(ctx);

        static auto sampler = agl::TextureSampler();
        sampler.applyTextureData(*apply);

        agl::utl::ImageFilter2D::drawColorQuadTriangle(ctx, sead::Color4f::cBlack, 1.0f);
        agl::utl::ImageFilter2D::drawTextureChannel(ctx, sampler, *viewport, gbuffer->mChannel, sead::Vector2f(1280.f/apply->mSurface.mWidth, 720.f/apply->mSurface.mHeight), sead::Vector2f::zero);
    
    }

    sead::Camera *cam;
    __asm("MOV %0, X28" : "=r" (cam));

    sead::Projection *projection;
    __asm("MOV %0, X26" : "=r" (projection));

    viewport->apply(ctx, (sead::LogicalFrameBuffer &)buffer);
}

HOOK_DEFINE_TRAMPOLINE(GetTexBufferHook) {
    static void Callback(al::GBufferArray *buf) {
        auto gbuffer = DevGuiManager::instance()->getHookSettings()->getGBufferSettings();
        
        gbuffer->mBuffer = buf;

        Orig(buf);
    }
};

void exlSetupGraphicsHooks() {
    InitGraphicsInfoHook::InstallAtSymbol("_ZN2al22initGraphicsSystemInfoEPNS_5SceneEPKci");
    RegisterPresetHook::InstallAtSymbol("_ZN2al22GraphicsPresetDirector14registerPresetEPKcS2_S2_b");
    RequestPresetHook::InstallAtSymbol("_ZN2al22GraphicsPresetDirector13requestPresetEPKciiiRKN4sead7Vector3IfEE");
    RequestCubeMapHook::InstallAtSymbol("_ZN2al19ShaderCubeMapKeeper14requestCubeMapEiPKcS2_");
    exl::patch::CodePatcher p("_ZN2al3Sky14initFromPresetERKNS_13ActorInitInfoE", 0x50);
    p.BranchLinkInst((void*)SkyInitHook);

    GetTexBufferHook::InstallAtSymbol("_ZNK2al12GBufferArray21getGBufLightBufferTexEv");
    p.Seek("_ZNK2al12ViewRenderer8drawViewERKNS_8ViewInfoEPNS_14DrawSystemInfoERKNS_10ProjectionERKN4sead6CameraEPKN3agl12RenderBufferERKNS9_8ViewportEbbb", 0x199C);
    p.BranchLinkInst((void*) ViewportApplyHook);
}