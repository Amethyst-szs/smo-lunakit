#include "helpers/ImGuiHelper.h"

namespace ImGuiHelper {

void Vector3Drag(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float speed, float limit)
{
    if(!vec) return;

    ImGui::DragFloat3(prefixName, &vec->x, speed, -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

void Vector3Slide(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float limit, bool isNormalize)
{
    if(!vec) return;

    ImGui::SliderFloat3(prefixName, &vec->x, -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(isNormalize)
        vec->normalize();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

void Quat(const char* tooltip, sead::Quatf* quat)
{
    if(!quat)
        return;

    ImGui::DragFloat4("Quat", &quat->x, 0.05f, -1.f, 1.f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
}

}