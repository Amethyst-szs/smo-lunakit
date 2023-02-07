#include "filedevice/nin/seadNinSDFileDeviceNin.h"
#include "filedevice/seadFileDeviceMgr.h"
#include "filedevice/seadPath.h"

namespace sead
{
NinSDFileDevice::NinSDFileDevice() : NinFileDeviceBase("sd", "sd") {}

bool NinSDFileDevice::doIsAvailable_() const
{
    return FileDeviceMgr::instance()->hasMountedSd();
}

bool NinSDFileDevice::formatPathForFS_(BufferedSafeString* out, const SafeString& path) const
{
    out->format("%s:/smo/%s", mMountPoint.cstr(), path.cstr());
    Path::changeDelimiter(out, '/');
    return true;
}

}  // namespace sead
