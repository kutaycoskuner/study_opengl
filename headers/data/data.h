#pragma once
#ifndef D_DATA
#define D_DATA
#include "../abstract/material.h"
#include "../abstract/light.h"
#include "../abstract/transform.h"
#include <vector>
#include <string>
#include <map>

#include "../abstract/vector2.h"

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

class VertexData;


// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------

class StaticLights
{
public:
	static std::vector<DirectionalLight> predef_dlights;
};


struct ModelPath {
	std::string model_file;
};

struct ShaderPaths {
	std::string vrtx_shader_file;
	std::string frag_shader_file;
	std::string geo_shader_file = "";
};

struct TexturePaths {
	std::string color;
	std::string roughness;
	std::string normal;
	std::string specular;
	std::string emission;
};

struct TextureSet
{
	unsigned int color		= 0;
	unsigned int roughness	= 0;
	unsigned int normal		= 0;
	unsigned int specular	= 0;
	unsigned int emission	= 0;
};

class PathAfterDirectory
{
public:
	static const std::vector<ShaderPaths> shader_paths;
	static const std::vector<ModelPath> model_paths;
	static std::map<std::string, TexturePaths> texture_paths;
	static std::map<std::string, std::vector<std::string>> cubemap_texture_paths;
};

class OpenGLParams
{
public:
	static float border_color[4];
};

class VertexData
{
public:
	static float		origin[3];
	static float		skybox_vrts__pos[108];

	static float		cube_vrts__pos_uv[180];

	static float		cube_vrts__pos_norm_uv[288];
	static unsigned int cube_inds__pos_norm_uv[36];

	static float		plane_vrts__pos_tex[30];
	static float		plane_vrts__pos_norm_uv[48];
	static float		quad_vrts__pos_tex[24];
	static float		quad_vrts__pos_norm_tex[42];
	static float		quad_vrts__pos_col[30];

	static float		square_vrts[32];
	static unsigned int square_inds[6];

	static float		x_axis[12];
	static float		y_axis[12];

	static float		rectangle__vrts[8]; 
};

struct ComputedData
{
	std::vector<Vec2> translations2d;
	std::vector<Mat4> mat4;
};

struct Predef3DNode
{
public:
	float*						p_data;
	unsigned int				num_elements;
	unsigned int				stride;
	std::vector<unsigned int>	att_num_elements;
};

class PredefNameMaps
{
public:
	static std::map<std::string, Predef3DNode> predef3d_namemap;
};

struct ElementBools {
	// techniques
	bool wireframe_mode		= false;
	bool depth_testing		= false;
	bool stencil_testing	= false;
	bool blending			= false;
	bool partial_render		= false;
	bool indexed			= false;
	bool is_triangle		= true;
	bool is_using_tan_space = false;
	bool face_culling		= false;
	bool gamma				= false;
};

struct PrimitiveSceneNode
{
	std::string		name;
	std::string		vertex_array_name;
	Transform		transform;
	std::string		shader_name;
	std::string		texture_name;
	float			tiling_factor = 1.0f;
	Material		material;
	ElementBools	element_bools;
};

//
class PrimitiveSceneNodes
{
public:
	static PrimitiveSceneNode origin;
	static PrimitiveSceneNode points;
	static PrimitiveSceneNode single_cube;
	static PrimitiveSceneNode big_cube;
	static PrimitiveSceneNode cube_10_0;
	static PrimitiveSceneNode cube_0_10;
	static PrimitiveSceneNode box_10_0;
	static PrimitiveSceneNode box_0_10;
	static PrimitiveSceneNode ground_platform;
	static PrimitiveSceneNode small_plane;
	static PrimitiveSceneNode plane;
	static PrimitiveSceneNode plane01;
	static PrimitiveSceneNode light_placeholder;
	static PrimitiveSceneNode nobg_grass;
	static PrimitiveSceneNode transparent_window;
	static PrimitiveSceneNode paircube1;
	static PrimitiveSceneNode paircube2;
	static PrimitiveSceneNode axis_x;
	static PrimitiveSceneNode axis_z;
};

class PredefSceneLights
{
public:
	static DirectionalLight d_light;
	static PointLight p_light;
	static SpotLight s_light;
};

class PredefMaterial
{
public:
	static const Material emerald;
	static const Material jade;
	static const Material obsidian;
	static const Material pearl;
	static const Material ruby;
	static const Material turquoise;
	static const Material brass;
	static const Material bronze;
	static const Material chrome;
	static const Material copper;
	static const Material gold;
	static const Material silver;
	static const Material black_plastic;
	static const Material cyan_plastic;
	static const Material green_plastic;
	static const Material red_plastic;
	static const Material white_plastic;
	static const Material yellow_plastic;
	static const Material black_rubber;
	static const Material cyan_rubber;
	static const Material green_rubber;
	static const Material red_rubber;
	static const Material white_rubber;
	static const Material yellow_rubber;
};

#endif
