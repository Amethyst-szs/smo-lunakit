
/*
    Looking for LunaKit code?
    Head to src/program/devgui/DevGuiManager.h to get started!
*/



#include "lib.hpp"
#include "imgui_backend/imgui_impl_nvn.hpp"
#include "patches.hpp"
#include "fs.h"

#include "logger/Logger.hpp"
#include "logger/LoadLogger.hpp"

#include <basis/seadRawPrint.h>
#include <prim/seadSafeString.h>
#include <resource/seadResourceMgr.h>
#include <filedevice/nin/seadNinSDFileDeviceNin.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <resource/seadArchiveRes.h>
#include <heap/seadHeapMgr.h>
#include <devenv/seadDebugFontMgrNvn.h>
#include <gfx/seadTextWriter.h>
#include <gfx/seadViewport.h>
#include <gfx/seadPrimitiveRenderer.h>

#include "rs/util.hpp"

#include "game/StageScene/StageScene.h"
#include "game/System/GameSystem.h"
#include "game/System/Application.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerTrigger.h"
#include "game/GameData/GameProgressData.h"
#include "game/GameData/GameDataHolderWriter.h"
#include "game/GameData/GameDataFile.h"


#include "al/util.hpp"
#include "al/util/LiveActorUtil.h"
#include "al/byaml/ByamlIter.h"
#include "al/fs/FileLoader.h"
#include "al/resource/Resource.h"
#include "al/collision/KCollisionServer.h"
#include "al/collision/alCollisionUtil.h"

#include "imgui_nvn.h"
#include "helpers/InputHelper.h"
#include "init.h"
#include "helpers/PlayerHelper.h"
#include "helpers.h"
#include "game/GameData/GameDataFunction.h"
#include "al/LiveActor/LiveActor.h"
#include "game/StageScene/StageScene.h"
#include "logger/Logger.hpp"
#include "os/os_tick.hpp"
#include "patch/code_patcher.hpp"

#include "helpers/GetHelper.h"
#include "devgui/DevGuiManager.h"
#include "devgui/DevGuiHooks.h"

#include "update/UpdateHandler.h"

#include <typeinfo>

#include "ExceptionHandler.h"
#include "ghost/GhostManager.h"
#include "smo-tas/TAS.h"

namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

static const char* DBG_FONT_PATH = "ImGuiData/Font/nvn_font_jis1.ntx";
static const char* DBG_SHADER_PATH = "ImGuiData/Font/nvn_font_shader_jis1.bin";
static const char* DBG_TBL_PATH = "ImGuiData/Font/nvn_font_jis1_tbl.bin";

#define IMGUI_ENABLED true

sead::TextWriter *gTextWriter;

void drawLunaKit() {
    DevGuiManager::instance()->updateDisplay();
}

HOOK_DEFINE_TRAMPOLINE(SceneMovementHook) {
    static void Callback(al::Scene* scene) {
        auto* tas = TAS::instance();
        tas->setScene(scene);
        tas->updateNerve();
        auto* ghostManager = GhostManager::instance();
        ghostManager->setScene(scene);
        ghostManager->updateNerve();
        ghostManager->updateGhostNerve();
        Orig(scene);
    }
};

HOOK_DEFINE_TRAMPOLINE(SceneEndInitHook) {
    static void Callback(al::Scene* scene, al::ActorInitInfo const& info) {
        GhostManager::instance()->init(info);
        Orig(scene, info);
    }
};

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) {
    static void Callback(sead::FileDeviceMgr *thisPtr) {

        Orig(thisPtr);

        thisPtr->mMountedSd = nn::fs::MountSdCardForDebug("sd");

        sead::NinSDFileDevice *sdFileDevice = new sead::NinSDFileDevice();

        thisPtr->mount(sdFileDevice);
    }
};

HOOK_DEFINE_TRAMPOLINE(RedirectFileDevice) {
    static sead::FileDevice *
    Callback(sead::FileDeviceMgr *thisPtr, sead::SafeString &path, sead::BufferedSafeString *pathNoDrive) {

        sead::FixedSafeString<32> driveName;
        sead::FileDevice *device;

        if (!sead::Path::getDriveName(&driveName, path)) {

            device = thisPtr->findDevice("sd");

            if (!(device && device->isExistFile(path))) {

                device = thisPtr->getDefaultFileDevice();

                if (!device) {
                    return nullptr;
                }

            } else {
            }

        } else
            device = thisPtr->findDevice(driveName);

        if (!device)
            return nullptr;

        if (pathNoDrive != nullptr)
            sead::Path::getPathExceptDrive(pathNoDrive, path);

        return device;
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderLoadArc) {
    static sead::ArchiveRes *
    Callback(al::FileLoader *thisPtr, sead::SafeString &path, const char *ext, sead::FileDevice *device) {

        ResourceLoadLogger* log = ResourceLoadLogger::instance();

        if(log)
            log->pushTextToVector(path.cstr());

        sead::FileDevice *sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if (sdFileDevice && sdFileDevice->isExistFile(path))
            device = sdFileDevice;

        return Orig(thisPtr, path, ext, device);
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderIsExistFile) {
    static bool Callback(al::FileLoader *thisPtr, sead::SafeString &path, sead::FileDevice *device) {

        ResourceLoadLogger* log = ResourceLoadLogger::instance();
        
        if(log)
            log->pushTextToVector(path.cstr());

        sead::FileDevice *sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if (sdFileDevice && sdFileDevice->isExistFile(path))
            device = sdFileDevice;

        return Orig(thisPtr, path, device);
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderIsExistArchive) {
    static bool Callback(al::FileLoader *thisPtr, sead::SafeString &path, sead::FileDevice *device) {
        sead::FileDevice *sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if (sdFileDevice && sdFileDevice->isExistFile(path))
            device = sdFileDevice;

        return Orig(thisPtr, path, device);
    }
};

HOOK_DEFINE_REPLACE(ReplaceSeadPrint) {
    static void Callback(const char *format, ...) {
        va_list args;
        va_start(args, format);
        Logger::log(format, args);
        va_end(args);
    }
};

HOOK_DEFINE_TRAMPOLINE(GameSystemInit) {
    static void Callback(GameSystem *thisPtr) {
        sead::Heap *curHeap = sead::HeapMgr::instance()->getCurrentHeap();

        sead::DebugFontMgrJis1Nvn::createInstance(curHeap);

        if (al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_TBL_PATH)) {
            sead::DebugFontMgrJis1Nvn::instance()->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH,
                                                              0x100000);
        }


        // creates heap for LunaKit at 7MB directly off the Stationed heap
        sead::Heap* lkHeap = sead::ExpHeap::create(7000000, "LunaKitHeap", al::getStationedHeap(), 8,
            sead::Heap::HeapDirection::cHeapDirection_Forward, false);
        lkHeap->enableLock(true);

        sead::Heap* updaterHeap = sead::ExpHeap::create(2500000, "UpdateHeap", lkHeap, 8,
            sead::Heap::HeapDirection::cHeapDirection_Forward, false);


        Logger::instance().init(lkHeap).value;
        ResourceLoadLogger::createInstance(lkHeap);
        ResourceLoadLogger::instance()->init(lkHeap);

        DevGuiManager::createInstance(lkHeap);
        UpdateHandler::createInstance(updaterHeap);

        // create TAS instance on LunaKit heap
        TAS::createInstance(lkHeap);

        // create GhostManager instance on LunaKit heap
        GhostManager::createInstance(lkHeap);

        DevGuiManager::instance()->init(lkHeap);
        UpdateHandler::instance()->init(updaterHeap);

        sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::instance());

        al::GameDrawInfo *drawInfo = Application::instance()->mDrawInfo;

        agl::DrawContext *context = drawInfo->mDrawContext;
        agl::RenderBuffer *renderBuffer = drawInfo->mFirstRenderBuffer;

        sead::Viewport *viewport = new sead::Viewport(*renderBuffer);

        gTextWriter = new sead::TextWriter(context, viewport);

        gTextWriter->setupGraphics(context);

        gTextWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);

        Orig(thisPtr);

    }
};

HOOK_DEFINE_TRAMPOLINE(UpdateLunaKit) {
    static void Callback(HakoniwaSequence *thisPtr) {
        Orig(thisPtr);
        DevGuiManager::instance()->update();
    }
};

extern "C" void exl_main(void *x0, void *x1) {
    /* Setup hooking enviroment. */
    // envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    handler::installExceptionHandler([](handler::ExceptionInfo& info) {
        handler::printCrashReport(info);
        return false;
    });

    runCodePatches();

    GameSystemInit::InstallAtSymbol("_ZN10GameSystem4initEv");
    ReplaceSeadPrint::InstallAtSymbol("_ZN4sead6system5PrintEPKcz");

    // SD File Redirection
    RedirectFileDevice::InstallAtSymbol("_ZNK4sead13FileDeviceMgr18findDeviceFromPathERKNS_14SafeStringBaseIcEEPNS_22BufferedSafeStringBaseIcEE");
    FileLoaderLoadArc::InstallAtSymbol("_ZN2al10FileLoader16loadArchiveLocalERKN4sead14SafeStringBaseIcEEPKcPNS1_10FileDeviceE");
    CreateFileDeviceMgr::InstallAtSymbol("_ZN4sead13FileDeviceMgrC2Ev");
    FileLoaderIsExistFile::InstallAtSymbol("_ZNK2al10FileLoader11isExistFileERKN4sead14SafeStringBaseIcEEPNS1_10FileDeviceE");
    FileLoaderIsExistArchive::InstallAtSymbol("_ZNK2al10FileLoader14isExistArchiveERKN4sead14SafeStringBaseIcEEPNS1_10FileDeviceE");

    // TAS
    SceneMovementHook::InstallAtSymbol("_ZN2al5Scene8movementEv");
    SceneEndInitHook::InstallAtSymbol("_ZN2al5Scene7endInitERKNS_13ActorInitInfoE");

    // Debug Text Writer Drawing
    UpdateLunaKit::InstallAtSymbol("_ZNK16HakoniwaSequence8drawMainEv");

    // DevGui cheats
    DevGuiHooks::exlInstallDevGuiHooks(); // Located in devgui/DevGuiHooks.cpp

    // ImGui Hooks
#if IMGUI_ENABLED
    nvnImGui::InstallHooks();

    nvnImGui::addDrawFunc(drawLunaKit);
#endif
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
