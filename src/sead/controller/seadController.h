#pragma once

#include "container/seadOffsetList.h"
#include "controller/seadControllerBase.h"

namespace sead {
    class ControllerMgr;

    class ControllerAddon;

    namespace ControllerDefine {
        enum AddonId : int {
        };
        enum ControllerId : int {
            cController_FullKey = 0,
            cController_Handheld = 1,
            cController_JoyDual = 2,
            cController_JoyLeft = 3,
            cController_JoyRight = 4,
            cController_Unknown = 5,
            _15 = 15,
            _16 = 16
        };
        enum DeviceId : int {
        };

    }  // namespace ControllerDefine

    class Controller : public ControllerBase {
    SEAD_RTTI_OVERRIDE(Controller, ControllerBase)

    public:
        Controller(ControllerMgr *);

        virtual ~Controller();

        virtual void calc();

        virtual bool isConnected();

        ControllerAddon *getAddonByOrder(ControllerDefine::AddonId, int);

        ControllerAddon *getAddon(ControllerDefine::AddonId);

    protected:
        virtual void calcImpl_() = 0;

        virtual bool isIdle_();

        virtual void setIdle_();

    private:
        int mControllerId;
        ControllerMgr *mMgr;
        OffsetList<ControllerAddon> mAddonList;
        OffsetList<void *> _160;  // unknown type
    };

}  // namespace sead
