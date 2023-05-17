#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
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
};

struct UniformsPerFrame
{

};