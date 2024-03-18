#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix4.h"
#include "../abstract/material.h"
#include "../abstract/light.h"

// ------------------------------------------------------------------------------------------------
// ----- Blueprints
// ------------------------------------------------------------------------------------------------
struct UniformsPerObject
{
	float mix_value = 0.0f;
	Mat4 world_matrix;
	Mat4 world_normal_matrix;
	Material material;
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
	DirectionalLight light;
};

struct Uniforms
{
	UniformsPerObject	upo;
	UniformsPerView		upv;
	UniformsPerFrame	upf;
};