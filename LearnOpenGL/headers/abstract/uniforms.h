#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix4.h"

// ------------------------------------------------------------------------------------------------
// ----- Blueprints
// ------------------------------------------------------------------------------------------------
struct UniformsPerObject
{
	float mixValue;
	Mat4 transform;
	Mat4 world_matrix;
	Mat4 world_normal_matrix;
};

struct UniformsPerView
{
	Vec3 view_pos;
	Mat4 view_matrix;
	Mat4 projection_matrix;
	Mat4 view_proj_matrix;
};

struct UniformsPerFrame
{
	Vec3 light_color;
};

struct Uniforms
{
	UniformsPerObject	upo;
	UniformsPerView		upv;
	UniformsPerFrame	upf;
};