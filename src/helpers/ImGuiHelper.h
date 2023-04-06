#include "imgui.h"

#include "sead/prim/seadSafeString.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"

namespace ImGuiHelper {

    // Vector editors
    void drawVector3Drag(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float speed, float limit);
    void drawVector3Slide(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float limit, bool isNormalize);

    // Quaternion editors
    void drawQuat(const char* tooltip, sead::Quatf* quat);
};