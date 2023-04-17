#include "helpers/ImGuiHelper.h"

namespace ImGuiHelper {

void Vector3Drag(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float speed, float limit)
{
    if(!vec)
        return;

    float* vecArray[3];
    vecArray[0] = &vec->x;
    vecArray[1] = &vec->y;
    vecArray[2] = &vec->z;

    ImGui::DragFloat3(prefixName, *vecArray, speed, -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

void Vector3Slide(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float limit, bool isNormalize)
{
    if(!vec)
        return;

    float* vecArray[3];
    vecArray[0] = &vec->x;
    vecArray[1] = &vec->y;
    vecArray[2] = &vec->z;

    ImGui::SliderFloat3(prefixName, *vecArray, -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(isNormalize)
        vec->normalize();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

void Quat(const char* tooltip, sead::Quatf* quat)
{
    if(!quat)
        return;

    float* vecArray[4];
    vecArray[0] = &quat->w;
    vecArray[1] = &quat->x;
    vecArray[2] = &quat->y;
    vecArray[3] = &quat->z;

    ImGui::DragFloat4("Quat", *vecArray, 0.05f, -1.f, 1.f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

}