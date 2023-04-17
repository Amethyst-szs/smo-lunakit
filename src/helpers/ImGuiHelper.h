#include "imgui.h"

#include "sead/prim/seadSafeString.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"

#include "nn/oe.h"

#include "types.h"

namespace ImGuiHelper {

// Vector editors
void Vector3Drag(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float speed, float limit);
void Vector3Slide(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float limit, bool isNormalize);

// Quaternion editors
void Quat(const char* tooltip, sead::Quatf* quat);

};