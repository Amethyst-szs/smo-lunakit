#pragma once

#include "container/seadOffsetList.h"
#include "controller/seadControllerBase.h"
#include "seadControllerDefine.h"

namespace sead
{
class ControllerMgr;
class ControllerAddon;


class Controller : public ControllerBase
{
    SEAD_RTTI_OVERRIDE(Controller, ControllerBase)
public:
    Controller(ControllerMgr*);
    virtual ~Controller();
    virtual void calc();
    virtual bool isConnected();
    ControllerAddon* getAddonByOrder(ControllerDefine::AddonId, int) const;
    ControllerAddon* getAddon(ControllerDefine::AddonId);

protected:
    virtual void calcImpl_() = 0;
    virtual bool isIdle_();
    virtual void setIdle_();

private:
    int mControllerId;
    ControllerMgr* mMgr;
    OffsetList<ControllerAddon> mAddonList;
    OffsetList<void*> _160;  // unknown type
};

}  // namespace sead
