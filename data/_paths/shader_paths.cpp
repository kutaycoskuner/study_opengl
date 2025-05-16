// libraries
// ---------------------------------------------------------------------------------------
#include "path_data.h"
#include "shader_data.h"

#include <map>

//const std::unordered_map<std::string, ShaderPaths> PathAfterDirectory::shader_paths = {
    const std::map<ShaderID, ShaderResourceDescriptor> shader_map = {

    { ShaderID::Shader3D,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.0.3d_vrtx_shader.glsl",
                .frag = "1.0.3d_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AxisX,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.1.axis-x_vrtx_shader.glsl",
                .frag = "1.1.axis-x_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AxisZ,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.1.axis-z_vrtx_shader.glsl",
                .frag = "1.1.axis-z_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Diffuse,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.2.diffuse_vrtx_shader.glsl",
                .frag = "1.2.diffuse_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Green,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.3.green_vrtx_shader.glsl",
                .frag = "1.3.green_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Pink,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "1.4.pink_vrtx_shader.glsl",
                .frag = "1.4.pink_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Phong,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.0.phong_lit_vrtx_shader.glsl",
                .frag = "2.0.phong_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Lightmap,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.1.lightmap_lit_vrtx_shader.glsl",
                .frag = "2.1.lightmap_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::LightcasterDirectional,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.2.lightcaster-directional_lit_vrtx_shader.glsl",
                .frag = "2.2.lightcaster-directional_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::LightcasterPoint,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.2.lightcaster-point_lit_vrtx_shader.glsl",
                .frag = "2.2.lightcaster-point_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::LightcasterSpot,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.2.lightcaster-spot_lit_vrtx_shader.glsl",
                .frag = "2.2.lightcaster-spot_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::MultipleLights,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "2.3.multiplelights_lit_vrtx_shader.glsl",
                .frag = "2.3.multiplelights_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::DepthTesting,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.0.depthtesting_lit_vrtx_shader.glsl",
                .frag = "3.0.depthtesting_lit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::StencilTesting,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.1.stenciltesting_vrtx_shader.glsl",
                .frag = "3.1.stenciltesting_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::StencilTesting02,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.1.stenciltesting02_vrtx_shader.glsl",
                .frag = "3.1.stenciltesting02_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Blending,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.2.blending_vrtx_shader.glsl",
                .frag = "3.2.blending_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Framebuffer,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.4.framebuffer_vrtx_shader.glsl",
                .frag = "3.4.framebuffer_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Cubemap,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.5.cubemap_vrtx_shader.glsl",
                .frag = "3.5.cubemap_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::CubemapLit,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.6.cubemaplit_vrtx_shader.glsl",
                .frag = "3.6.cubemaplit_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AdvGLSLRed,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.8.advglsl-red_vrtx_shader.glsl",
                .frag = "3.8.advglsl-red_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AdvGLSLGreen,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.8.advglsl-green_vrtx_shader.glsl",
                .frag = "3.8.advglsl-green_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AdvGLSLBlue,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.8.advglsl-blue_vrtx_shader.glsl",
                .frag = "3.8.advglsl-blue_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::AdvGLSLYellow,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.8.advglsl-yellow_vrtx_shader.glsl",
                .frag = "3.8.advglsl-yellow_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Axes,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9.axes_vrtx_shader.glsl",
                .frag = "3.9.axes_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Explode,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9.explode_vrtx_shader.glsl",
                .frag = "3.9.explode_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Geo,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9.geo_vrtx_shader.glsl",
                .frag = "3.9.geo_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Normal,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9.normal_vrtx_shader.glsl",
                .frag = "3.9.normal_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Instance,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.10.instance_vrtx_shader.glsl",
                .frag = "3.10.instance_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Instance02,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.10.instance02_vrtx_shader.glsl",
                .frag = "3.10.instance02_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::BlinnPhong,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.1.blinnphong_vrtx_shader.glsl",
                .frag = "4.1.blinnphong_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::BlinnPhong2,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.1.blinnphong2_vrtx_shader.glsl",
                .frag = "4.1.blinnphong2_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Gamma,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.2.gamma_vrtx_shader.glsl",
                .frag = "4.2.gamma_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::ShadowMap,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.3.shadowmap_vrtx_shader.glsl",
                .frag = "4.3.shadowmap_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::LightShadow,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.3.light-shadow_vrtx_shader.glsl",
                .frag = "4.3.light-shadow_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::PLightShadow,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.4.plight-shadow_vrtx_shader.glsl",
                .frag = "4.4.plight-shadow_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::ShadowMapPL,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.4.shadowmap-pl_vrtx_shader.glsl",
                .frag = "4.4.shadowmap-pl_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Normal01,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.5.normal01_vrtx_shader.glsl",
                .frag = "4.5.normal01_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Normal02,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.6.normal02_vrtx_shader.glsl",
                .frag = "4.6.normal02_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Parallax,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.7.parallax_vrtx_shader.glsl",
                .frag = "4.7.parallax_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::HDR,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.8.hdr_vrtx_shader.glsl",
                .frag = "4.8.hdr_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Bloom,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.9.bloom_vrtx_shader.glsl",
                .frag = "4.9.bloom_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::GaussianBlur,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
                .frag = "post_process/gaussian-blur_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::DeferredGeometryPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.10.1.deferred-geometry_vrtx_shader.glsl",
                .frag = "4.10.1.deferred-geometry_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::DeferredLightingPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.10.2.deferred-lighting_vrtx_shader.glsl",
                .frag = "4.10.2.deferred-lighting_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::SSAOGeometryPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.11.1.ssao-geometry_vrtx_shader.glsl",
                .frag = "4.11.1.ssao-geometry_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::SSAODrawPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.11.2.ssao-draw_vrtx_shader.glsl",
                .frag = "4.11.2.ssao-draw_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::SSAOBlurPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
                .frag = "4.11.3.ssao-blur_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::SSAOLightingPass,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
                .frag = "4.11.4.ssao-lighting_frag_shader.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

};
//
//const std::unordered_map<std::string, ShaderPaths> PathAfterDirectory::shader_paths = {
//    {"3d",
//        { .vrtx = "1.0.3d_vrtx_shader.glsl",
//          .frag = "1.0.3d_frag_shader.glsl" }},
//    
//    {"axis-x",
//        { .vrtx = "1.1.axis-x_vrtx_shader.glsl",
//          .frag = "1.1.axis-x_frag_shader.glsl" }},
//    
//    {"axis-z",
//        { .vrtx = "1.1.axis-z_vrtx_shader.glsl",
//          .frag = "1.1.axis-z_frag_shader.glsl" }},
//    
//    {"diffuse",
//        { .vrtx = "1.2.diffuse_vrtx_shader.glsl",
//          .frag = "1.2.diffuse_frag_shader.glsl" }},
//    
//    {"green",
//        { .vrtx = "1.3.green_vrtx_shader.glsl",
//          .frag = "1.3.green_frag_shader.glsl" }},
//    
//    {"pink",
//        { .vrtx = "1.4.pink_vrtx_shader.glsl",
//          .frag = "1.4.pink_frag_shader.glsl" }},
//    
//    {"phong",
//        { .vrtx = "2.0.phong_lit_vrtx_shader.glsl",
//          .frag = "2.0.phong_lit_frag_shader.glsl" }},
//    
//    {"lightmap",
//        { .vrtx = "2.1.lightmap_lit_vrtx_shader.glsl",
//          .frag = "2.1.lightmap_lit_frag_shader.glsl" }},
//    
//    {"lightcaster-directional",
//        { .vrtx = "2.2.lightcaster-directional_lit_vrtx_shader.glsl",
//          .frag = "2.2.lightcaster-directional_lit_frag_shader.glsl" }},
//    
//    {"lightcaster-point",
//        { .vrtx = "2.2.lightcaster-point_lit_vrtx_shader.glsl",
//          .frag = "2.2.lightcaster-point_lit_frag_shader.glsl" }},
//    
//    {"lightcaster-spot",
//        { .vrtx = "2.2.lightcaster-spot_lit_vrtx_shader.glsl",
//          .frag = "2.2.lightcaster-spot_lit_frag_shader.glsl" }},
//    
//    {"multiplelights",
//        { .vrtx = "2.3.multiplelights_lit_vrtx_shader.glsl",
//          .frag = "2.3.multiplelights_lit_frag_shader.glsl" }},
//    
//    {"depthtesting",
//        { .vrtx = "3.0.depthtesting_lit_vrtx_shader.glsl",
//          .frag = "3.0.depthtesting_lit_frag_shader.glsl" }},
//    
//    {"stenciltesting",
//        { .vrtx = "3.1.stenciltesting_vrtx_shader.glsl",
//          .frag = "3.1.stenciltesting_frag_shader.glsl" }},
//
//    {"stenciltesting02",
//        { .vrtx = "3.1.stenciltesting02_vrtx_shader.glsl",
//          .frag = "3.1.stenciltesting02_frag_shader.glsl" }},
//    
//    {"blending",
//        { .vrtx = "3.2.blending_vrtx_shader.glsl",
//          .frag = "3.2.blending_frag_shader.glsl" }},
//    
//    {"framebuffer",
//        { .vrtx = "3.4.framebuffer_vrtx_shader.glsl",
//          .frag = "3.4.framebuffer_frag_shader.glsl" }},
//    
//    {"cubemap",
//        { .vrtx = "3.5.cubemap_vrtx_shader.glsl",
//          .frag = "3.5.cubemap_frag_shader.glsl" }},
//    
//    {"cubemaplit",
//        { .vrtx = "3.6.cubemaplit_vrtx_shader.glsl",
//          .frag = "3.6.cubemaplit_frag_shader.glsl" }},
//
//    {"advglsl-red",
//        { .vrtx = "3.8.advglsl-red_vrtx_shader.glsl",
//          .frag = "3.8.advglsl-red_frag_shader.glsl" }},
//
//    {"advglsl-green",
//        { .vrtx = "3.8.advglsl-green_vrtx_shader.glsl",
//          .frag = "3.8.advglsl-green_frag_shader.glsl" }},
//    
//    {"advglsl-blue",
//        { .vrtx = "3.8.advglsl-blue_vrtx_shader.glsl",
//          .frag = "3.8.advglsl-blue_frag_shader.glsl" }},
//
//    {"advglsl-yellow",
//        { .vrtx = "3.8.advglsl-yellow_vrtx_shader.glsl",
//          .frag = "3.8.advglsl-yellow_frag_shader.glsl" }},
//    
//    {"axes",
//        { .vrtx = "3.9.axes_vrtx_shader.glsl",
//          .frag = "3.9.axes_frag_shader.glsl",
//          .geom = "3.9.axes_geo_shader.glsl" }},
//    
//    {"explode",
//        { .vrtx = "3.9.explode_vrtx_shader.glsl",
//          .frag = "3.9.explode_frag_shader.glsl",
//          .geom = "3.9.explode_geo_shader.glsl" }},
//    
//    {"geo",
//        { .vrtx = "3.9.geo_vrtx_shader.glsl",
//          .frag = "3.9.geo_frag_shader.glsl",
//          .geom = "3.9.geo_geo_shader.glsl" }},
//    
//    {"normal",
//        { .vrtx = "3.9.normal_vrtx_shader.glsl",
//          .frag = "3.9.normal_frag_shader.glsl",
//          .geom = "3.9.normal_geo_shader.glsl" }},
//    
//    {"instance",
//        { .vrtx = "3.10.instance_vrtx_shader.glsl",
//          .frag = "3.10.instance_frag_shader.glsl" }},
//    
//    {"instance02",
//        { .vrtx = "3.10.instance02_vrtx_shader.glsl",
//          .frag = "3.10.instance02_frag_shader.glsl" }},
//    
//    {"blinnphong",
//        { .vrtx = "4.1.blinnphong_vrtx_shader.glsl",
//          .frag = "4.1.blinnphong_frag_shader.glsl" }},
//    
//    {"blinnphong2",
//        { .vrtx = "4.1.blinnphong2_vrtx_shader.glsl",
//          .frag = "4.1.blinnphong2_frag_shader.glsl" }},
//    
//    {"gamma",
//        { .vrtx = "4.2.gamma_vrtx_shader.glsl",
//          .frag = "4.2.gamma_frag_shader.glsl" }},
//    
//    {"shadowmap",
//        { .vrtx = "4.3.shadowmap_vrtx_shader.glsl",
//          .frag = "4.3.shadowmap_frag_shader.glsl" }},
//    
//    {"light-shadow",
//        { .vrtx = "4.3.light-shadow_vrtx_shader.glsl",
//          .frag = "4.3.light-shadow_frag_shader.glsl" }},
//    
//    {"plight-shadow",
//        { .vrtx = "4.4.plight-shadow_vrtx_shader.glsl",
//          .frag = "4.4.plight-shadow_frag_shader.glsl" }},
//    
//    {"shadowmap-pl",
//        { .vrtx = "4.4.shadowmap-pl_vrtx_shader.glsl",
//          .frag = "4.4.shadowmap-pl_frag_shader.glsl",
//          .geom = "4.4.shadowmap-pl_geo_shader.glsl" }},
//    
//    {"normal01",
//        { .vrtx = "4.5.normal01_vrtx_shader.glsl",
//          .frag = "4.5.normal01_frag_shader.glsl" }},
//    
//    {"normal02",
//        { .vrtx = "4.6.normal02_vrtx_shader.glsl",
//          .frag = "4.6.normal02_frag_shader.glsl" }},
//    
//    {"parallax",
//        { .vrtx = "4.7.parallax_vrtx_shader.glsl",
//          .frag = "4.7.parallax_frag_shader.glsl" }},
//    
//    {"hdr",
//        { .vrtx = "4.8.hdr_vrtx_shader.glsl",
//          .frag = "4.8.hdr_frag_shader.glsl" }},
//    
//    {"bloom",
//        { .vrtx = "4.9.bloom_vrtx_shader.glsl",
//          .frag = "4.9.bloom_frag_shader.glsl" }},
//    
//    {"gaussian-blur",
//        { .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
//          .frag = "post_process/gaussian-blur_frag_shader.glsl" }},
//
//    {"deferred-geometry-pass",
//        { .vrtx = "4.10.1.deferred-geometry_vrtx_shader.glsl",
//          .frag = "4.10.1.deferred-geometry_frag_shader.glsl" }},
//
//    {"deferred-lighting-pass",
//        { .vrtx = "4.10.2.deferred-lighting_vrtx_shader.glsl",
//          .frag = "4.10.2.deferred-lighting_frag_shader.glsl" }},
//
//    {"ssao-geometry-pass",
//      { .vrtx = "4.11.1.ssao-geometry_vrtx_shader.glsl",
//        .frag = "4.11.1.ssao-geometry_frag_shader.glsl" }},
//
//    {"ssao-draw-pass",
//      { .vrtx = "4.11.2.ssao-draw_vrtx_shader.glsl",
//        .frag = "4.11.2.ssao-draw_frag_shader.glsl" }},
//        
//    {"ssao-blur-pass",
//      { .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
//        .frag = "4.11.3.ssao-blur_frag_shader.glsl" }},
//
//    {"ssao-lighting-pass",
//      { .vrtx = "post_process/gaussian-blur_vrtx_shader.glsl",
//        .frag = "4.11.4.ssao-lighting_frag_shader.glsl" }}
//};