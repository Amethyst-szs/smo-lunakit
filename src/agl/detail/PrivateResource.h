#pragma once

#include <filedevice/seadArchiveFileDevice.h>
#include <resource/seadArchiveRes.h>

#include "agl/TextureSampler.h"

namespace agl {
    namespace detail {
        class PrivateResource : public sead::hostio::Node {
            SEAD_SINGLETON_DISPOSER(PrivateResource);
            PrivateResource();
            virtual ~PrivateResource();
            sead::Heap* mHeap;
            void* unk2[7];
            sead::ArchiveFileDevice* mFileDevice;
            sead::ArchiveRes* mNvnArchive;
            void* unk3;
            TextureSampler* mCursorSampler1;
            TextureSampler* mCursorSampler2;
            GPUMemBlockBase mCursorMemory;
            void* unk4[7];
        public:
            void createArchive(sead::ArchiveRes*);

            TextureSampler* getCursorTextureSampler() { return mCursorSampler2; }
        };
    };
};