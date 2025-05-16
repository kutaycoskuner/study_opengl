#pragma once

#include "../abstract/light.h"
#include "../abstract/material.h"
#include "node_data.h"

#include <vector>
#include <map>
#include <string>



// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

class StaticLights
{
public:
	static std::vector<DirectionalLight> predef_dlights;
};


class PredefNameMaps
{
public:
	static std::map<std::string, Predef3DNode> predef3d_namemap;
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
