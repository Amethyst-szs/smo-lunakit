#pragma once

#include "AreaShape.h"
#include "al/actor/Placement.h"
#include "al/area/AreaShape.h"
#include "al/hio/HioNode.h"
#include "al/scene/SceneObjHolder.h"
#include "al/switch/StageSwitchKeeper.h"
#include "sead/math/seadMatrix.h"
#include "sead/math/seadVector.h"

namespace al {

    struct AreaInitInfo;

    class AreaObj : public al::IUseStageSwitch, public al::IUseSceneObjHolder, public al::HioNode {
    public:
        AreaObj(char const *);

        virtual const char *getName(void) const override;
        virtual StageSwitchKeeper *getStageSwitchKeeper(void) const override;
        virtual void initStageSwitchKeeper(void) override;
        virtual void init(al::AreaInitInfo const&);
        virtual bool isInVolume(sead::Vector3f const&) const;
        virtual bool isInVolumeOffset(sead::Vector3f const&,float) const;
        virtual SceneObjHolder *getSceneObjHolder(void) const override;

        const char *mName; // 0x10
        AreaShape *mAreaShape; // 0x18
        StageSwitchKeeper *mStageSwitchKeeper; // 0x20
        SceneObjHolder *mSceneObjHolder; // 0x28
        sead::Matrix34f mAreaMtx; // 0x30
        al::PlacementInfo *mPlacementInfo; // 0x60
        int mPriority; // 0x68
        bool mIsValid; // 0x6C

    };
}