#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix.h"

// ------------------------------------------------------------------------------------------------
// ----- Blueprints
// ------------------------------------------------------------------------------------------------
struct UniformsPerObject
{
	float mixValue;
	Mat4 transform;
	Mat4 world_matrix;
};

struct UniformsPerView
{
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