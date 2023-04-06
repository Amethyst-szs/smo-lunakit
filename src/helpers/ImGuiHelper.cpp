#include "helpers/ImGuiHelper.h"

void ImGuiHelper::drawVector3Drag(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float speed, float limit)
{
    if(!vec)
        return;

    const char* symbols = "XYZ";
    sead::FixedSafeString<0xf> sliderName(prefixName);

    ImGui::BeginGroup();

    for(uint i = 0; i < strlen(symbols); i++) {
        sliderName.append(symbols[i]);
        ImGui::DragFloat(sliderName.cstr(), &vec->e[i], speed, -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
        sliderName.chop(1);
    }

    ImGui::EndGroup();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
    
    ImGui::Separator();
}

void ImGuiHelper::drawVector3Slide(const char* prefixName, const char* tooltip, sead::Vector3f* vec, float limit, bool isNormalize)
{
    if(!vec)
        return;

    const char* symbols = "XYZ";
    sead::FixedSafeString<0xf> sliderName(prefixName);

    ImGui::BeginGroup();

    for(uint i = 0; i < strlen(symbols); i++) {
        sliderName.append(symbols[i]);
        ImGui::SliderFloat(sliderName.cstr(), &vec->e[i], -limit, limit, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
        sliderName.chop(1);
    }

    if(isNormalize)
        vec->normalize();

    ImGui::EndGroup();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
    
    ImGui::Separator();
}

void ImGuiHelper::drawQuat(const char* tooltip, sead::Quatf* quat)
{
    if(!quat)
        return;

    ImGui::BeginGroup();

    ImGui::DragFloat("QW", &quat->w, 0.05f, 0.f, 0.f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
    ImGui::SliderFloat("QX", &quat->x, -1.f, 1.f, "%.3f", ImGuiSliderFlags_NoRoundToFormat);
    ImGui::SliderFloat("QY", &quat->y, -1.f, 1.f, "%.3f", ImGuiSliderFlags_NoRoundToFormat);
    ImGui::SliderFloat("QZ", &quat->z, -1.f, 1.f, "%.3f", ImGuiSliderFlags_NoRoundToFormat);

    // quat->normalize();

    ImGui::EndGroup();

    if(ImGui::IsItemHovered())
        ImGui::SetTooltip(tooltip);
    
    ImGui::Separator();
}