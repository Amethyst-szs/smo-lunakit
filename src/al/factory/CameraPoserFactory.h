#pragma once

#include "Factory.h"
#include "logger.hpp"

namespace cc {
    template <class T>
    al::CameraPoser *createCustomCameraPoser(const char *name)
    {
        return new T(name);
    };
}

namespace al {

    class CameraPoser;

    template <class T>
    CameraPoser* createCameraPoserFunction(const char *name);

    typedef CameraPoser* (*createCameraPoser)(const char* name);
    
    class CameraPoserFactory : public Factory<createCameraPoser> {
        public:
            CameraPoserFactory(const char *fName) __attribute__((noinline)) {
                this->factoryName = fName;
                this->actorTable = nullptr;
                this->factoryCount = 0;
            };

            // use this to log cameras being created by the camera poser factory
            // virtual const char *convertName(char const *name) const override
            // {
            //     Logger::log("Creating Camera: %s\n", name);
            //     return name;
            // };

            virtual CameraPoser *createEntranceCameraPoser(void) const;
            // return new al::CameraPoserEntrance(スタート);

            int mLastUsedIndex = 0;
    };
}

namespace alCameraPoserFactoryFunction {
    void initAndCreateTableFromOtherTable2(al::CameraPoserFactory *,al::NameToCreator<al::createCameraPoser> const*,int,al::NameToCreator<al::createCameraPoser> const*,int);
    void initAndCreateTableWithAnotherFactory(al::CameraPoserFactory *,al::CameraPoserFactory const*,al::NameToCreator<al::createCameraPoser> const*,int);
    void initAndCreateTableWithPresetPosers(al::CameraPoserFactory *,al::NameToCreator<al::createCameraPoser> const*,int);
}