// libraries
// ---------------------------------------------------------------------------------------
#include "data.h"

const std::unordered_map<std::string, ShaderPaths> PathAfterDirectory::shader_paths = {
    {"3d",
        { .vrtx = "1.0.3d_vrtx_shader.glsl",
          .frag = "1.0.3d_frag_shader.glsl" }},
    
    {"axis-x",
        { .vrtx = "1.1.axis-x_vrtx_shader.glsl",
          .frag = "1.1.axis-x_frag_shader.glsl" }},
    
    {"axis-z",
        { .vrtx = "1.1.axis-z_vrtx_shader.glsl",
          .frag = "1.1.axis-z_frag_shader.glsl" }},
    
    {"diffuse",
        { .vrtx = "1.2.diffuse_vrtx_shader.glsl",
          .frag = "1.2.diffuse_frag_shader.glsl" }},
    
    {"green",
        { .vrtx = "1.3.green_vrtx_shader.glsl",
          .frag = "1.3.green_frag_shader.glsl" }},
    
    {"pink",
        { .vrtx = "1.4.pink_vrtx_shader.glsl",
          .frag = "1.4.pink_frag_shader.glsl" }},
    
    {"phong",
        { .vrtx = "2.0.phong_lit_vrtx_shader.glsl",
          .frag = "2.0.phong_lit_frag_shader.glsl" }},
    
    {"lightmap",
        { .vrtx = "2.1.lightmap_lit_vrtx_shader.glsl",
          .frag = "2.1.lightmap_lit_frag_shader.glsl" }},
    
    {"lightcaster-directional",
        { .vrtx = "2.2.lightcaster-directional_lit_vrtx_shader.glsl",
          .frag = "2.2.lightcaster-directional_lit_frag_shader.glsl" }},
    
    {"lightcaster-point",
        { .vrtx = "2.2.lightcaster-point_lit_vrtx_shader.glsl",
          .frag = "2.2.lightcaster-point_lit_frag_shader.glsl" }},
    
    {"lightcaster-spot",
        { .vrtx = "2.2.lightcaster-spot_lit_vrtx_shader.glsl",
          .frag = "2.2.lightcaster-spot_lit_frag_shader.glsl" }},
    
    {"multiplelights",
        { .vrtx = "2.3.multiplelights_lit_vrtx_shader.glsl",
          .frag = "2.3.multiplelights_lit_frag_shader.glsl" }},
    
    {"depthtesting",
        { .vrtx = "3.0.depthtesting_lit_vrtx_shader.glsl",
          .frag = "3.0.depthtesting_lit_frag_shader.glsl" }},
    
    {"stenciltesting",
        { .vrtx = "3.1.stenciltesting_vrtx_shader.glsl",
          .frag = "3.1.stenciltesting_frag_shader.glsl" }},

    {"stenciltesting02",
        { .vrtx = "3.1.stenciltesting02_vrtx_shader.glsl",
          .frag = "3.1.stenciltesting02_frag_shader.glsl" }},
    
    {"blending",
        { .vrtx = "3.2.blending_vrtx_shader.glsl",
          .frag = "3.2.blending_frag_shader.glsl" }},
    
    {"framebuffer",
        { .vrtx = "3.4.framebuffer_vrtx_shader.glsl",
          .frag = "3.4.framebuffer_frag_shader.glsl" }},
    
    {"cubemap",
        { .vrtx = "3.5.cubemap_vrtx_shader.glsl",
          .frag = "3.5.cubemap_frag_shader.glsl" }},
    
    {"cubemaplit",
        { .vrtx = "3.6.cubemaplit_vrtx_shader.glsl",
          .frag = "3.6.cubemaplit_frag_shader.glsl" }},

    {"advglsl-red",
        { .vrtx = "3.8.advglsl-red_vrtx_shader.glsl",
          .frag = "3.8.advglsl-red_frag_shader.glsl" }},

    {"advglsl-green",
        { .vrtx = "3.8.advglsl-green_vrtx_shader.glsl",
          .frag = "3.8.advglsl-green_frag_shader.glsl" }},
    
    {"advglsl-blue",
        { .vrtx = "3.8.advglsl-blue_vrtx_shader.glsl",
          .frag = "3.8.advglsl-blue_frag_shader.glsl" }},

    {"advglsl-yellow",
        { .vrtx = "3.8.advglsl-yellow_vrtx_shader.glsl",
          .frag = "3.8.advglsl-yellow_frag_shader.glsl" }},
    
    {"axes",
        { .vrtx = "3.9.axes_vrtx_shader.glsl",
          .frag = "3.9.axes_frag_shader.glsl",
          .geom = "3.9.axes_geo_shader.glsl" }},
    
    {"explode",
        { .vrtx = "3.9.explode_vrtx_shader.glsl",
          .frag = "3.9.explode_frag_shader.glsl",
          .geom = "3.9.explode_geo_shader.glsl" }},
    
    {"geo",
        { .vrtx = "3.9.geo_vrtx_shader.glsl",
          .frag = "3.9.geo_frag_shader.glsl",
          .geom = "3.9.geo_geo_shader.glsl" }},
    
    {"normal",
        { .vrtx = "3.9.normal_vrtx_shader.glsl",
          .frag = "3.9.normal_frag_shader.glsl",
          .geom = "3.9.normal_geo_shader.glsl" }},
    
    {"instance",
        { .vrtx = "3.10.instance_vrtx_shader.glsl",
          .frag = "3.10.instance_frag_shader.glsl" }},
    
    {"instance02",
        { .vrtx = "3.10.instance02_vrtx_shader.glsl",
          .frag = "3.10.instance02_frag_shader.glsl" }},
    
    {"blinnphong",
        { .vrtx = "4.1.blinnphong_vrtx_shader.glsl",
          .frag = "4.1.blinnphong_frag_shader.glsl" }},
    
    {"blinnphong2",
        { .vrtx = "4.1.blinnphong2_vrtx_shader.glsl",
          .frag = "4.1.blinnphong2_frag_shader.glsl" }},
    
    {"gamma",
        { .vrtx = "4.2.gamma_vrtx_shader.glsl",
          .frag = "4.2.gamma_frag_shader.glsl" }},
    
    {"shadowmap",
        { .vrtx = "4.3.shadowmap_vrtx_shader.glsl",
          .frag = "4.3.shadowmap_frag_shader.glsl" }},
    
    {"light-shadow",
        { .vrtx = "4.3.light-shadow_vrtx_shader.glsl",
          .frag = "4.3.light-shadow_frag_shader.glsl" }},
    
    {"plight-shadow",
        { .vrtx = "4.4.plight-shadow_vrtx_shader.glsl",
          .frag = "4.4.plight-shadow_frag_shader.glsl" }},
    
    {"shadowmap-pl",
        { .vrtx = "4.4.shadowmap-pl_vrtx_shader.glsl",
          .frag = "4.4.shadowmap-pl_frag_shader.glsl",
          .geom = "4.4.shadowmap-pl_geo_shader.glsl" }},
    
    {"normal01",
        { .vrtx = "4.5.normal01_vrtx_shader.glsl",
          .frag = "4.5.normal01_frag_shader.glsl" }},
    
    {"normal02",
        { .vrtx = "4.6.normal02_vrtx_shader.glsl",
          .frag = "4.6.normal02_frag_shader.glsl" }},
    
    {"parallax",
        { .vrtx = "4.7.parallax_vrtx_shader.glsl",
          .frag = "4.7.parallax_frag_shader.glsl" }},
    
    {"hdr",
        { .vrtx = "4.8.hdr_vrtx_shader.glsl",
          .frag = "4.8.hdr_frag_shader.glsl" }},
    
    {"bloom",
        { .vrtx = "4.9.bloom_vrtx_shader.glsl",
          .frag = "4.9.bloom_frag_shader.glsl" }},
    
    {"gaussian-blur",
        { .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
          .frag = "post_process/gaussian-blur_frag_shader.glsl" }},

    {"deferred",
        { .vrtx = "4.10.deferred_vrtx_shader.glsl",
          .frag = "4.10.deferred_frag_shader.glsl" }}
};