#pragma once

#include "al/resource/Resource.h"
#include <container/seadPtrArray.h>

namespace al {
    class GraphicsSystemInfo;
    class GraphicsPreset;

    class GraphicsPresetDirector {
        public:
        al::GraphicsSystemInfo *mGraphicsSystemInfo;
        al::Resource *mPresetsArchive;
        sead::PtrArrayImpl mPtrArray1;
        al::GraphicsPreset *mPreset1;
        al::GraphicsPreset *mPreset2;
        sead::PtrArrayImpl mPtrArray2;
        //char unknown;
        //_BYTE gap_41[7];
        //sead::FixedSafeString64 mStr1;
        //_BYTE gap_A0[32];
        //sead::FixedSafeString64 mStr2;
        //_BYTE gap_118[32];
    };
}