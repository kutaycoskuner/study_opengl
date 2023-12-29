#pragma once
#ifndef D_DATA
#define D_DATA
#include "../abstract/material.h"
#include "../abstract/light.h"
#include <vector>
#include <string>
//
class StaticLights
{
public:
	static std::vector<DirectionalLight> predef_dlights;
};


class ShaderPaths
{
public:
	static const std::vector<std::vector<std::string>> shader_paths;
};

class OpenGLParams
{
public:
	static float border_color[4];
};

class ObjToDraw
{
public:
	static float		cube_vrts__pos_uv[180];

	static float		cube_vrts__pos_norm_uv[288];
	static unsigned int cube_inds__pos_norm_uv[36];
	
	static float		square_vrts[32];
	static unsigned int square_inds[6];

	static float		x_axis[12];
	static float		y_axis[12];
};

class ObjWorldPositions
{
public:
	static std::vector<Vec3> obj_world_positions;
};

class PresetMaterial
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
