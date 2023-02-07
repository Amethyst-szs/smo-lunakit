/**
 * @file ShaderHolder.h
 * @brief Defines classes for shader storage.
 */

#pragma once

#include <heap/seadHeap.h>
#include <container/seadPtrArray.h>

#include "agl/shader/ShaderProgram.h"
#include "agl/shader/ShaderProgramArchive.h"
#include "types.h"

namespace agl
{
    namespace detail
    {

        static const char* shaderArcs[] = {
            "agl_common",
            "agl_technique",
            "agl_technique_pfx",
            "agl_technique_lght",
            "agl_technique_lght_lpp",
            "agl_technique_shdw"
        };

        struct ProgramEntry {
            int mUnkInt;
            const char *mProgramName;
        };

        static ProgramEntry programs[] = {
            {0, "dev_util"},
            {0, "depth_visualize"},
            {0, "texture"},
            {0, "reduce_2"},
            {0, "reduce_4"},
            {0, "reduce_8"},
            {0, "reduce_16"},
            {2, "color_correction"},
            {2, "color_correction_map"},
            {0, "xlu_snap"},
            {0, "image_filter_gaussian"},
            {0, "image_filter_cubic"},
            {0, "image_filter_blur"},
            {0, "texture_mult_color"},
            {0, "red"},
            {0, "green"},
            {0, "blue"},
            {0, "alpha"},
            {0, "depth_raw"},
            {0, "depth_linear"},
            {0, "depth_linear_array"},
            {0, "depth_2d"},
            {0, "depth_2d_array_quad"},
            {0, "depth_2d_min"},
            {0, "depth_2d_array_min"},
            {0, "depth_2d_max"},
            {0, "depth_2d_array_max"},
            {0, "color_2d_array_quad"},
            {0, "color_2d_min"},
            {0, "color_2d_array_min"},
            {0, "color_2d_max"},
            {0, "color_2d_array_max"},
            {0, "uint"},
            {0, "uint_array"},
            {0, "depth_mask"},
            {0, "luminance"},
            {0, "texture_2d_array"},
            {0, "texture_3d"},
            {0, "texture_cube_map"},
            {0, "texture_cube_map_array"},
            {0, "texture_clrmtx_2d"},
            {0, "texture_clrmtx_2d_array"},
            {0, "texture_texcoord"},
            {0, "texture_texcoord_mult_color"},
            {0, "texture_multi_sample_1x"},
            {0, "texture_multi_sample_2x"},
            {0, "texture_multi_sample_4x"},
            {0, "texture_multi_sample_8x"},
            {0, "alpha_modify"},
            {0, "texture_color_drift"},
            {0, "color_quad"},
            {0, "clear_quad"},
            {0, "top_bottom_color"},
            {0, "texture_gamma"},
            {0, "clear"},
            {0, "draw_imm"},
            {0, "draw_fan"},
            {0, "draw_capsule"},
            {0, "frame_buffer_flip_y"},
            {0, "frame_buffer_no_flip"},
            {2, "bloom_mask"},
            {2, "bloom_gaussian"},
            {2, "bloom_compose"},
            {2, "bloom_reduce"},
            {2, "hdr_compose"},
            {2, "dof_near_mask"},
            {2, "dof_mipmap"},
            {2, "dof_depth_mask"},
            {2, "dof_final"},
            {2, "dof_indirect"},
            {2, "dof_vignetting"},
            {2, "dof_expand_reduce"},
            {2, "fxaa"},
            {2, "fxaa_coloronly"},
            {2, "fxaa_luma"},
            {2, "fxaa_reprojection"},
            {2, "fxaa_debug"},
            {2, "filter_aa_reprojection"},
            {2, "reduce_aa"},
            {2, "smaa_line_detection"},
            {2, "smaa_weight_calculation"},
            {2, "smaa_compose"},
            {2, "smaa_resolve"},
            {2, "smaac_line_detection"},
            {2, "smaac_weight_calculation"},
            {2, "smaac_utility"},
            {3, "lightmap"},
            {3, "lightmap_clear"},
            {3, "local_lightmap"},
            {4, "light_pre_pass_point_light"},
            {4, "light_pre_pass_spot_light"},
            {4, "light_pre_pass_proj_light"},
            {4, "light_pre_pass_dev"},
            {1, "multi_filter_reduce"},
            {1, "multi_filter_expand"},
            {5, "static_depth_shadow"},
            {0, "cubemap_gaussian"},
            {0, "cubemap_head_extract"},
            {0, "cubemap_head_convolute_first"},
            {0, "cubemap_head_convolute_other"},
            {0, "cubemap_hdr_encode"},
            {0, "cubemap_draw_illuminant"},
            {0, "nv12decode"},
            {1, "screen_pick"},
            {0, "debug_cubemap"},
            {5, "depth_shadow_debug"},
            {5, "vsm"},
            {5, "ssao_ao_buffer"},
            {5, "ssao_blur"},
            {5, "ssao_reduce"},
            {5, "ssao_mask"},
            {1, "occlusion_query"},
            {1, "occlusion_renderer_clear_buf"},
            {1, "occlusion_renderer"},
            {1, "occluded_effect_lensflare"},
            {0, "texture_compress"},
            {0, "texture_compress_hq"},
            {5, "shadow_mask"},
            {1, "radial_blur"},
            {1, "radial_blur_compose"},
            {3, "ssii"},
            {3, "ssii_ref"},
            {3, "ssii_reduce"},
            {3, "ssii_reduce_g"},
            {3, "ssii_pre_render"},
            {3, "ssii_expand"},
            {3, "ssii_anti_howling"},
            {1, "normal_map"},
            {2, "auto_exposure"},
            {3, "sssss_blur"},
            {3, "sssss_expand_sss"},
            {3, "sssss_reduce"},
            {3, "sssss_merge"},
            {3, "sssss_merge_weight"},
            {2, "glare_filter_seed"},
            {2, "glare_filter_blur"},
            {2, "glare_filter_depth"},
            {2, "glare_filter_clear"},
            {2, "flare_filter_flare"},
            {2, "flare_filter_copy"},
            {3, "planar_reflection"},
            {5, "shadow_pre_pass"},
            {5, "shadow_pre_pass_reduce"},
            {5, "shadow_pre_pass_blur"},
            {5, "shadow_pre_pass_post"},
            {5, "screen_space_self_shadow"},
            {5, "screen_space_self_shadow_create_hiz"},
            {1, "decal_simple"},
            {1, "decal_trail"},
            {1, "decal_texture_drawer"},
            {1, "normal_drawer_post"},
            {2, "sky_dome"},
            {2, "sky_screen"},
            {2, "sky_cloud"},
            {2, "sky_dither"},
            {0, "debug_primitive"},
            {0, "debug_shape_instanced"},
            {0, "debug_point_instanced"},
            {0, "debug_line_instanced"},
            {0, "debug_triangle_instanced"},
            {0, "cubemap_irradiance"},
            {0, "cubemap_sh"},
            {0, "cubemap_sh_point"},
            {0, "cubemap_sh_occlusion"},
            {3, "local_reflection_mask"},
            {3, "local_reflection_filter"},
            {3, "local_reflection_gaussian_filter"},
            {3, "local_reflection_depth_filter"},
            {3, "local_reflection_specular"},
            {3, "local_reflection_specular_vec4"},
            {3, "local_reflection_jittered_copy"},
            {3, "local_reflection_debug"},
            {0, "debug_sh_volume_vtx"},
            {0, "debug_sh_volume_frag"},
            {0, "debug_sh_volume_hemi_light"},
            {3, "sh_volume_lighting"},
            {3, "sh_volume_cubemap_lighting"},
            {3, "sh_volume_clear_all_slices"},
            {3, "sh_volume_clear_single_slice"},
            {3, "sh_volume_point"},
            {3, "sh_volume_point_mrt"},
            {3, "sh_volume_rect_mrt"},
            {3, "sh_volume_copy_mrt"},
            {3, "sh_volume_copy_mrt_single_slice"},
            {3, "sh_volume_diff_update_mrt"},
            {3, "sh_volume_copy_cubemap_mrt"},
            {3, "sh_volume_cubemap_face_filter"},
            {2, "vdm"},
            {1, "cloud"},
            {1, "volume_mask_reducedepth"},
            {1, "volume_mask_layer"},
            {1, "volume_mask_raymarch"},
            {1, "volume_mask_drawtex"},
            {1, "volume_mask_debug"},
            {2, "sky_transmittance"},
            {2, "sky_irradiance"},
            {2, "sky_inscatter"},
            {2, "sky_delta_inscatter"},
            {2, "sky_copy_irradiance"},
            {2, "sky_copy_inscatter"},
            {2, "sky_bake_inscatter"},
            {2, "sky_bake_irradiance"},
            {2, "sky_bake_range_transmittance"},
            {2, "sky_postfx_sky"},
            {2, "sky_postfx_ground"},
            {1, "star_render"}
        };
    
        class ShaderHolder
        {
        SEAD_SINGLETON_DISPOSER(ShaderHolder)
        public:
        
            ShaderHolder();

            void* unkPtr1; // _20
            
            sead::PtrArray<agl::ShaderProgram> mShaders; // _28

        // private:
            agl::ShaderProgram* mShaderBuf[ACNT(programs)];
            agl::ShaderProgramArchive mArcCommon;
            agl::ShaderProgramArchive mArcTechnique;
            agl::ShaderProgramArchive mArcTechnique_pfx;
            agl::ShaderProgramArchive mArcTechnique_lght;
            agl::ShaderProgramArchive mArcTechnique_lght_lpp;
            agl::ShaderProgramArchive mArcTechnique_shdw;
        };      
    };
};