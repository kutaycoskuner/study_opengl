#pragma once

#include "shader_data.h"
#include "../abstract/material.h"
#include "../abstract/transform.h"

#include <string>
#include <vector>


// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

class OpenGLParams
{
public:
	static float border_color[4];
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
	std::string		name; // todo: remove
	std::string		vertex_array_name;
	Transform		transform;
	ShaderID		shader_id;
	std::string		texture_name;
	float			tiling_factor = 1.0f;
	Material		material;
	ElementBools	element_bools;
};


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


struct SceneNode
{
	std::string		name;
	Transform		transform;

	// Constructor
	SceneNode(const std::string& node_name = "", const Transform& node_transform = Transform())
		: name(node_name), transform(node_transform) {}
};


struct Predef3DNode
{
public:
	float*						p_data;
	unsigned int				num_elements;
	unsigned int				stride;
	std::vector<unsigned int>	att_num_elements;
};


struct TextureSet
{
	unsigned int color		  = 0;
	unsigned int roughness	  = 0;
	unsigned int normal	      = 0;
	unsigned int specular	  = 0;
	unsigned int emission	  = 0;
	unsigned int displacement = 0;
};