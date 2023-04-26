#pragma once
#include <cassert>

struct Vec3
{
	float x;
	float y;
	float z;

	// default constructor
	Vec3() :x(0), y(0), z(0) {}

	// parameter constructior
	Vec3(float in_x, float in_y, float in_z) :x(in_x), y(in_y), z(in_z) {}
	Vec3(const Vec3& vec) :x(vec.x), y(vec.y), z(vec.z) {}

};

static void testVectorUnit()
{
	Vec3 default_vec;
	assert(default_vec.x == 0.0f && default_vec.y == 0.0f && default_vec.z == 0.0f);

	Vec3 param_vec(1, 0, 1);
	assert(param_vec.x == 1.0f && param_vec.y == 0.0f && param_vec.z == 1.0f);

	Vec3 param2_vec(param_vec);
	assert(param2_vec.x == 2.0f && param2_vec.y == 0.0f && param2_vec.z == 1.0f);
}