#pragma once
// ----------------------------------------------------------------------------
//				libraries
// ----------------------------------------------------------------------------

#include "../../headers/utils/utilities.h"
#include "path_data.h"

#include <iostream>
#include <unordered_set>

// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------
struct ShaderData;

// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

// Enum for shader identifiers
enum class ShaderID
{
    Shader3D,
    AxisX,
    AxisZ,
    Diffuse,
    Green,
    Pink,
    Phong,
    Lightmap,
    LightcasterDirectional,
    LightcasterPoint,
    LightcasterSpot,
    MultipleLights,
    DepthTesting,
    StencilTesting,
    StencilTesting02,
    Blending,
    Framebuffer,
    Cubemap,
    CubemapLit,
    AdvGLSLRed,
    AdvGLSLGreen,
    AdvGLSLBlue,
    AdvGLSLYellow,
    Axes,
    Explode,
    Geo,
    Normal,
    Instance,
    Instance02,
    BlinnPhong,
    BlinnPhong2,
    Gamma,
    ShadowMap,
    LightShadow,
    PLightShadow,
    ShadowMapPL,
    Normal01,
    Normal02,
    Parallax,
    HDR,
    Bloom,
    GaussianBlur,
    DeferredGeometryPass,
    DeferredLightingPass,
    SSAOGeometryPass,
    SSAODrawPass,
    SSAOBlurPass,
    SSAOLightingPass
    ,
    NumOfShaderIDs
};

enum class RenderViewMode
{
    ILLUMINATION,
    COLOR,
    DEPTH,
    NORMAL,
    POSITION,
    SPECULAR,
    SSAO_RAW,
    SSAO_BLUR
};

// Final shader data container
struct ShaderResourceDescriptor
{
    ShaderPaths                                   paths;
    std::unordered_set<RenderViewMode>            renderview_modes;
};