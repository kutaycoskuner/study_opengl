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
                .vrtx = "1.0-3d-vrtx.glsl",
                .frag = "1.0-3d-frag.glsl",
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
                .vrtx = "1.1-axis_x-vrtx.glsl",
                .frag = "1.1-axis_x-frag.glsl",
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
                .vrtx = "1.1-axis_z-vrtx.glsl",
                .frag = "1.1-axis_z-frag.glsl",
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
                .vrtx = "1.2-diffuse-vrtx.glsl",
                .frag = "1.2-diffuse-frag.glsl",
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
                .vrtx = "1.3-green-vrtx.glsl",
                .frag = "1.3-green-frag.glsl",
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
                .vrtx = "1.4-pink-vrtx.glsl",
                .frag = "1.4-pink-frag.glsl",
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
                .vrtx = "2.0-phong_lit-vrtx.glsl",
                .frag = "2.0-phong_lit-frag.glsl",
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
                .vrtx = "2.1-lightmap_lit-vrtx.glsl",
                .frag = "2.1-lightmap_lit-frag.glsl",
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
                .vrtx = "2.2-lightcaster_directional_lit-vrtx.glsl",
                .frag = "2.2-lightcaster_directional_lit-frag.glsl",
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
                .vrtx = "2.2-lightcaster_point_lit-vrtx.glsl",
                .frag = "2.2-lightcaster_point_lit-frag.glsl",
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
                .vrtx = "2.2-lightcaster_spot_lit-vrtx.glsl",
                .frag = "2.2-lightcaster_spot_lit-frag.glsl",
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
                .vrtx = "2.3-multiplelights_lit-vrtx.glsl",
                .frag = "2.3-multiplelights_lit-frag.glsl",
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
                .vrtx = "3.0-depthtesting_lit-vrtx.glsl",
                .frag = "3.0-depthtesting_lit-frag.glsl",
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
                .vrtx = "3.1-stenciltesting-vrtx.glsl",
                .frag = "3.1-stenciltesting-frag.glsl",
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
                .vrtx = "3.1-stenciltesting02-vrtx.glsl",
                .frag = "3.1-stenciltesting02-frag.glsl",
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
                .vrtx = "3.2-blending-vrtx.glsl",
                .frag = "3.2-blending-frag.glsl",
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
                .vrtx = "3.4-framebuffer-vrtx.glsl",
                .frag = "3.4-framebuffer-frag.glsl",
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
                .vrtx = "3.5-cubemap-vrtx.glsl",
                .frag = "3.5-cubemap-frag.glsl",
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
                .vrtx = "3.6-cubemaplit-vrtx.glsl",
                .frag = "3.6-cubemaplit-frag.glsl",
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
                .vrtx = "3.8-advglsl_red-vrtx.glsl",
                .frag = "3.8-advglsl_red-frag.glsl",
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
                .vrtx = "3.8-advglsl_green-vrtx.glsl",
                .frag = "3.8-advglsl_green-frag.glsl",
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
                .vrtx = "3.8-advglsl_blue-vrtx.glsl",
                .frag = "3.8-advglsl_blue-frag.glsl",
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
                .vrtx = "3.8-advglsl_yellow-vrtx.glsl",
                .frag = "3.8-advglsl_yellow-frag.glsl",
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
                .vrtx = "3.9-axes-vrtx.glsl",
                .frag = "3.9-axes-frag.glsl",
                .geom = "3.9-axes-geo.glsl"
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Explode,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9-explode-vrtx.glsl",
                .frag = "3.9-explode-frag.glsl",
                .geom = "3.9-explode-geo.glsl"
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Geo,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9-vrtx.glsl",
                .frag = "3.9-frag.glsl",
                .geom = "3.9-geo.glsl"
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Normal,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.9-normal-vrtx.glsl",
                .frag = "3.9-normal-frag.glsl",
                .geom = "3.9-normal-geo.glsl"
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Instance,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "3.10-instance-vrtx.glsl",
                .frag = "3.10-instance-frag.glsl",
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
                .vrtx = "3.10-instance02-vrtx.glsl",
                .frag = "3.10-instance02-frag.glsl",
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
                .vrtx = "4.1-blinnphong-vrtx.glsl",
                .frag = "4.1-blinnphong-frag.glsl",
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
                .vrtx = "4.1-blinnphong2-vrtx.glsl",
                .frag = "4.1-blinnphong2-frag.glsl",
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
                .vrtx = "4.2-gamma-vrtx.glsl",
                .frag = "4.2-gamma-frag.glsl",
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
                .vrtx = "4.3-shadowmap-vrtx.glsl",
                .frag = "4.3-shadowmap-frag.glsl",
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
                .vrtx = "4.3-light_shadow-vrtx.glsl",
                .frag = "4.3-light_shadow-frag.glsl",
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
                .vrtx = "4.4-plight_shadow-vrtx.glsl",
                .frag = "4.4-plight_shadow-frag.glsl",
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
                .vrtx = "4.4-shadowmap_pl-vrtx.glsl",
                .frag = "4.4-shadowmap_pl-frag.glsl",
                .geom = "4.4-shadowmap_pl-geo.glsl"
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION
            }
        }
    },

    { ShaderID::Normal01,
        ShaderResourceDescriptor {
            .paths = ShaderPaths{
                .vrtx = "4.5-normal01-vrtx.glsl",
                .frag = "4.5-normal01-frag.glsl",
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
                .vrtx = "4.6-normal02-vrtx.glsl",
                .frag = "4.6-normal02-frag.glsl",
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
                .vrtx = "4.7-parallax-vrtx.glsl",
                .frag = "4.7-parallax-frag.glsl",
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
                .vrtx = "4.8-hdr-vrtx.glsl",
                .frag = "4.8-hdr-frag.glsl",
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
                .vrtx = "4.9-bloom-vrtx.glsl",
                .frag = "4.9-bloom-frag.glsl",
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
                .vrtx = "post_process/gaussian_blur-vrtx.glsl",
                .frag = "post_process/gaussian_blur-frag.glsl",
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
                .vrtx = "4.10.1-deferred_geometry-vrtx.glsl",
                .frag = "4.10.1-deferred_geometry-frag.glsl",
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
                .vrtx = "4.10.2-deferred_lighting-vrtx.glsl",
                .frag = "4.10.2-deferred_lighting-frag.glsl",
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
                .vrtx = "4.11.1-ssao_geometry-vrtx.glsl",
                .frag = "4.11.1-ssao_geometry-frag.glsl",
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
                .vrtx = "4.11.2-ssao_draw-vrtx.glsl",
                .frag = "4.11.2-ssao_draw-frag.glsl",
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
                .vrtx = "post_process/gaussian_blur-vrtx.glsl",
                .frag = "4.11.3-ssao_blur-frag.glsl",
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
                .vrtx = "post_process/gaussian_blur-vrtx.glsl",
                .frag = "4.11.4-ssao_lighting-frag.glsl",
                .geom = ""
            },
            .renderview_modes = {
                RenderViewMode::ILLUMINATION,
            }
        }
    },

};
//
//const std::unordered_map<std::string, ShaderPaths> PathAfterDirectory::shader_paths = {
//    {"3d",
//        { .vrtx = "1.0-3d-vrtx.glsl",
//          .frag = "1.0-3d-frag.glsl" }},
//    
//    {"axis-x",
//        { .vrtx = "1.1-axis_x-vrtx.glsl",
//          .frag = "1.1-axis_x-frag.glsl" }},
//    
//    {"axis-z",
//        { .vrtx = "1.1-axis_z-vrtx.glsl",
//          .frag = "1.1-axis_z-frag.glsl" }},
//    
//    {"diffuse",
//        { .vrtx = "1.2-diffuse-vrtx.glsl",
//          .frag = "1.2-diffuse-frag.glsl" }},
//    
//    {"green",
//        { .vrtx = "1.3-green-vrtx.glsl",
//          .frag = "1.3-green-frag.glsl" }},
//    
//    {"pink",
//        { .vrtx = "1.4-pink-vrtx.glsl",
//          .frag = "1.4-pink-frag.glsl" }},
//    
//    {"phong",
//        { .vrtx = "2.0-phong_lit-vrtx.glsl",
//          .frag = "2.0-phong_lit-frag.glsl" }},
//    
//    {"lightmap",
//        { .vrtx = "2.1-lightmap_lit-vrtx.glsl",
//          .frag = "2.1-lightmap_lit-frag.glsl" }},
//    
//    {"lightcaster-directional",
//        { .vrtx = "2.2-lightcaster_directional_lit-vrtx.glsl",
//          .frag = "2.2-lightcaster_directional_lit-frag.glsl" }},
//    
//    {"lightcaster-point",
//        { .vrtx = "2.2-lightcaster_point_lit-vrtx.glsl",
//          .frag = "2.2-lightcaster_point_lit-frag.glsl" }},
//    
//    {"lightcaster-spot",
//        { .vrtx = "2.2-lightcaster_spot_lit-vrtx.glsl",
//          .frag = "2.2-lightcaster_spot_lit-frag.glsl" }},
//    
//    {"multiplelights",
//        { .vrtx = "2.3-multiplelights_lit-vrtx.glsl",
//          .frag = "2.3-multiplelights_lit-frag.glsl" }},
//    
//    {"depthtesting",
//        { .vrtx = "3.0-depthtesting_lit-vrtx.glsl",
//          .frag = "3.0-depthtesting_lit-frag.glsl" }},
//    
//    {"stenciltesting",
//        { .vrtx = "3.1-stenciltesting-vrtx.glsl",
//          .frag = "3.1-stenciltesting-frag.glsl" }},
//
//    {"stenciltesting02",
//        { .vrtx = "3.1-stenciltesting02-vrtx.glsl",
//          .frag = "3.1-stenciltesting02-frag.glsl" }},
//    
//    {"blending",
//        { .vrtx = "3.2-blending-vrtx.glsl",
//          .frag = "3.2-blending-frag.glsl" }},
//    
//    {"framebuffer",
//        { .vrtx = "3.4-framebuffer-vrtx.glsl",
//          .frag = "3.4-framebuffer-frag.glsl" }},
//    
//    {"cubemap",
//        { .vrtx = "3.5-cubemap-vrtx.glsl",
//          .frag = "3.5-cubemap-frag.glsl" }},
//    
//    {"cubemaplit",
//        { .vrtx = "3.6-cubemaplit-vrtx.glsl",
//          .frag = "3.6-cubemaplit-frag.glsl" }},
//
//    {"advglsl-red",
//        { .vrtx = "3.8-advglsl_red-vrtx.glsl",
//          .frag = "3.8-advglsl_red-frag.glsl" }},
//
//    {"advglsl-green",
//        { .vrtx = "3.8-advglsl_green-vrtx.glsl",
//          .frag = "3.8-advglsl_green-frag.glsl" }},
//    
//    {"advglsl-blue",
//        { .vrtx = "3.8-advglsl_blue-vrtx.glsl",
//          .frag = "3.8-advglsl_blue-frag.glsl" }},
//
//    {"advglsl-yellow",
//        { .vrtx = "3.8-advglsl_yellow-vrtx.glsl",
//          .frag = "3.8-advglsl_yellow-frag.glsl" }},
//    
//    {"axes",
//        { .vrtx = "3.9-axes-vrtx.glsl",
//          .frag = "3.9-axes-frag.glsl",
//          .geom = "3.9-axes-geo.glsl" }},
//    
//    {"explode",
//        { .vrtx = "3.9-explode-vrtx.glsl",
//          .frag = "3.9-explode-frag.glsl",
//          .geom = "3.9-explode-geo.glsl" }},
//    
//    {"geo",
//        { .vrtx = "3.9-vrtx.glsl",
//          .frag = "3.9-frag.glsl",
//          .geom = "3.9-geo.glsl" }},
//    
//    {"normal",
//        { .vrtx = "3.9-normal-vrtx.glsl",
//          .frag = "3.9-normal-frag.glsl",
//          .geom = "3.9-normal-geo.glsl" }},
//    
//    {"instance",
//        { .vrtx = "3.10-instance-vrtx.glsl",
//          .frag = "3.10-instance-frag.glsl" }},
//    
//    {"instance02",
//        { .vrtx = "3.10-instance02-vrtx.glsl",
//          .frag = "3.10-instance02-frag.glsl" }},
//    
//    {"blinnphong",
//        { .vrtx = "4.1-blinnphong-vrtx.glsl",
//          .frag = "4.1-blinnphong-frag.glsl" }},
//    
//    {"blinnphong2",
//        { .vrtx = "4.1-blinnphong2-vrtx.glsl",
//          .frag = "4.1-blinnphong2-frag.glsl" }},
//    
//    {"gamma",
//        { .vrtx = "4.2-gamma-vrtx.glsl",
//          .frag = "4.2-gamma-frag.glsl" }},
//    
//    {"shadowmap",
//        { .vrtx = "4.3-shadowmap-vrtx.glsl",
//          .frag = "4.3-shadowmap-frag.glsl" }},
//    
//    {"light-shadow",
//        { .vrtx = "4.3-light_shadow-vrtx.glsl",
//          .frag = "4.3-light_shadow-frag.glsl" }},
//    
//    {"plight-shadow",
//        { .vrtx = "4.4-plight_shadow-vrtx.glsl",
//          .frag = "4.4-plight_shadow-frag.glsl" }},
//    
//    {"shadowmap-pl",
//        { .vrtx = "4.4-shadowmap_pl-vrtx.glsl",
//          .frag = "4.4-shadowmap_pl-frag.glsl",
//          .geom = "4.4-shadowmap_pl-geo.glsl" }},
//    
//    {"normal01",
//        { .vrtx = "4.5-normal01-vrtx.glsl",
//          .frag = "4.5-normal01-frag.glsl" }},
//    
//    {"normal02",
//        { .vrtx = "4.6-normal02-vrtx.glsl",
//          .frag = "4.6-normal02-frag.glsl" }},
//    
//    {"parallax",
//        { .vrtx = "4.7-parallax-vrtx.glsl",
//          .frag = "4.7-parallax-frag.glsl" }},
//    
//    {"hdr",
//        { .vrtx = "4.8-hdr-vrtx.glsl",
//          .frag = "4.8-hdr-frag.glsl" }},
//    
//    {"bloom",
//        { .vrtx = "4.9-bloom-vrtx.glsl",
//          .frag = "4.9-bloom-frag.glsl" }},
//    
//    {"gaussian-blur",
//        { .vrtx = "post_process/gaussian_blur-vrtx.glsl",
//          .frag = "post_process/gaussian_blur-frag.glsl" }},
//
//    {"deferred-geometry-pass",
//        { .vrtx = "4.10.1-deferred_geometry-vrtx.glsl",
//          .frag = "4.10.1-deferred_geometry-frag.glsl" }},
//
//    {"deferred-lighting-pass",
//        { .vrtx = "4.10.2-deferred_lighting-vrtx.glsl",
//          .frag = "4.10.2-deferred_lighting-frag.glsl" }},
//
//    {"ssao-geometry-pass",
//      { .vrtx = "4.11.1-ssao_geometry-vrtx.glsl",
//        .frag = "4.11.1-ssao_geometry-frag.glsl" }},
//
//    {"ssao-draw-pass",
//      { .vrtx = "4.11.2-ssao_draw-vrtx.glsl",
//        .frag = "4.11.2-ssao_draw-frag.glsl" }},
//        
//    {"ssao-blur-pass",
//      { .vrtx = "post_process/gaussian_blur-vrtx.glsl",
//        .frag = "4.11.3-ssao_blur-frag.glsl" }},
//
//    {"ssao-lighting-pass",
//      { .vrtx = "post_process/gaussian_blur-vrtx.glsl",
//        .frag = "4.11.4-ssao_lighting-frag.glsl" }}
//};