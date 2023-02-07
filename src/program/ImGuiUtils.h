#pragma once

namespace ImGui
{
    inline void SetupImGuiStyle( bool bStyleDark_, float alpha_  )
    {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
        style.Alpha = 1.0f;
        style.WindowRounding = 7.0f;
        style.FrameRounding = 5.0f;
        style.ScrollbarSize = 18.f;
        style.ScrollbarRounding = 15.f;
        style.GrabRounding = 15.f;
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.MouseCursorScale = 1.2f;

        style.Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.99f, 0.99f, 0.99f, 0.99f);
        style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style.Colors[ImGuiCol_Border]                = ImVec4(1.00f, 0.96f, 0.98f, 0.99f);
        style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.80f, 0.76f, 0.78f, 0.59f);
        style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.9f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 0.96f, 0.98f, 0.51f);
        style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.76f, 0.78f, 1.00f);
        style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.99f, 0.92f, 0.96f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        style.Colors[ImGuiCol_CheckMark]             = ImVec4(1.f, .3f, .3f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.79f, 0.44f, 0.68f, 0.75f);
        style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(1.f, .3f, .3f, 1.00f);
        style.Colors[ImGuiCol_Button]                = ImVec4(0.79f, 0.44f, 0.68f, 0.50f);
        style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.79f, 0.44f, 0.68f, 0.9f);
        style.Colors[ImGuiCol_ButtonActive]          = ImVec4(1.f, .3f, .3f, 1.00f);
        style.Colors[ImGuiCol_Header]                = ImVec4(0.79f, 0.44f, 0.68f, 0.61f);
        style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.79f, 0.44f, 0.68f, 0.90f);
        style.Colors[ImGuiCol_HeaderActive]          = ImVec4(1.f, .3f, .3f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.79f, 0.44f, 0.68f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.f, .3f, .3f, 0.95f);
        style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.85f, 0.70f, 0.78f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

        if( bStyleDark_ )
        {
            for (int i = 0; i <= ImGuiCol_COUNT; i++)
            {
                ImVec4& col = style.Colors[i];
                float H, S, V;
                ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );

                if( S < 0.1f )
                {
                   V = 1.0f - V;
                }
                ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
                if( col.w < 1.00f )
                {
                    col.w *= alpha_;
                }
            }
        }
        else
        {
            for (int i = 0; i <= ImGuiCol_COUNT; i++)
            {
                ImVec4& col = style.Colors[i];
                if( col.w < 1.00f )
                {
                    col.x *= alpha_;
                    col.y *= alpha_;
                    col.z *= alpha_;
                    col.w *= alpha_;
                }
            }
        }
    }
}