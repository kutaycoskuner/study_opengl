#pragma once
#ifndef D_DATA
#define D_DATA
#include "../abstract/material.h"
#include "../abstract/light.h"
#include "../abstract/transform.h"
#include <vector>
#include <string>
#include <map>
//
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
	unsigned int color;
	unsigned int roughness;
	unsigned int normal;
	unsigned int specular;
	unsigned int emission;
};

class RelativePaths
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

class Predef3D
{
public:
	static float		skybox_vrts__pos[108];

	static float		cube_vrts__pos_uv[180];

	static float		cube_vrts__pos_norm_uv[288];
	static unsigned int cube_inds__pos_norm_uv[36];

	static float		plane_vrts__pos_tex[30];
	static float		quad_vrts__pos_tex[24];

	static float		square_vrts[32];
	static unsigned int square_inds[6];

	static float		x_axis[12];
	static float		y_axis[12];
};

struct ElementBools {
	// techniques
	bool wireframe_mode;
	bool depth_testing;
	bool stencil_testing;
	bool blending;
	bool partial_render;
	bool indexed;
};

struct PredefSceneElement
{
	std::string		name;
	float*			mesh;
	Transform		transform;
	std::string		shader_name;
	std::string		texture_name;
	Material		material;
	ElementBools	element_bools;
};

//
class PredefSceneElements
{
public:
	static PredefSceneElement single_cube;
	static PredefSceneElement big_cube;
	static PredefSceneElement cube_10_0;
	static PredefSceneElement cube_0_10;
	static PredefSceneElement box_10_0;
	static PredefSceneElement box_0_10;
	static PredefSceneElement ground_plane;
	static PredefSceneElement light_placeholder;
	static PredefSceneElement nobg_grass;
	static PredefSceneElement transparent_window;
	static PredefSceneElement paircube1;
	static PredefSceneElement paircube2;
	static PredefSceneElement axis_x;
	static PredefSceneElement axis_z;
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
