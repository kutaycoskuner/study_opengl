#include "../../headers/abstract/vector3.h"

//bool compareApprox(const float&a, const float& b);


static void unitTest_Vec3_defaultConstructor()
{
	Vec3 default_vec;
	assert(default_vec.x == 0.0f && default_vec.y == 0.0f && default_vec.z == 0.0f);
}

static void unitTest_Vec3_paramConstructor()
{
	Vec3 param_vec(1, 0, 1);
	assert(param_vec.x == 1.0f && param_vec.y == 0.0f && param_vec.z == 1.0f);
	float param = 4.0f;
	Vec3 param_vec2(param);
	assert(param_vec2.x == param && param_vec2.y == param && param_vec2.z == param);
}

static void unitTest_Vec3_copyConstructor()
{
	Vec3 param_vec(1, 0, 1);
	Vec3 param2_vec(param_vec);
	assert(param2_vec.x == 1.0f && param2_vec.y == 0.0f && param2_vec.z == 1.0f);
}

static void unitTest_Vec3_math()
{
	Vec3 v1 = { 1.0f };
	Vec3 v2 = { 2.0f };
	Vec3 v3 = v1 + v2;
	float param = 3.0f;
	// v-v addition
	assert(v3.x == param && v3.y == param && v3.z == param);
	v3 = v2 - v1;
	// v-v subtraction
	assert(math_utils::compareApprox(v3.x,1.0f) && math_utils::compareApprox(v3.y,1.0f) && math_utils::compareApprox(v3.z, 1.0f));
	v3 = v2 + v1;
	// negation
	Vec3 v4 = -v3;
	assert(v4.x == -v3.x && v4.y == -v3.y && v4.z == -v3.z);	
	// v-s addition
	Vec3 v5 = v3 + 1;
	assert(v5.x == param + 1.0f && 
		   v5.y == param + 1.0f && 
		   v5.z == param + 1.0f);
	// v-s subtraction
	v5 = v3 - 1;
	assert(v5.x == param - 1.0f &&
		   v5.y == param - 1.0f &&
		   v5.z == param - 1.0f);
	// length
	assert(v3.length() == sqrtf(param * param * param));
	// normalization
	assert(math_utils::compareApprox(v5.normalized().length(), 1.0f));

	// dot product
	Vec3 ver(0, 1, 0);
	Vec3 hor(1, 0, 0);
	float dp = math_utils::dot3d(hor, ver);
	assert(dp == 0);
	ver = (1.0f, 5.0f, 0.0f);
	hor = (-1.0f, -5.0f, 0.0f);
	dp = math_utils::dot3d(hor, ver);
	assert(dp == -1 * hor.length() * ver.length());

	// cross product
	Vec3 xAxis = Vec3(1, 0, 0);
	Vec3 yAxis = Vec3(0, 1, 0);
	Vec3 zAxis = Vec3(0, 0, 1);
	Vec3 origin = Vec3(0, 0, 0);
	assert(math_utils::cross3d(xAxis, yAxis) == zAxis);
	assert(math_utils::cross3d(xAxis, zAxis) == -yAxis);
	assert(math_utils::cross3d(yAxis, zAxis) == xAxis);
	assert(math_utils::cross3d(yAxis, xAxis) == -zAxis);
	assert(math_utils::cross3d(zAxis, xAxis) == yAxis);
	assert(math_utils::cross3d(zAxis, yAxis) == -xAxis);


	assert(math_utils::cross3d(xAxis, -yAxis) == -zAxis);
	assert(math_utils::cross3d(xAxis, -zAxis) == yAxis);
	assert(math_utils::cross3d(yAxis, -zAxis) == -xAxis);
	assert(math_utils::cross3d(yAxis, -xAxis) == zAxis);
	assert(math_utils::cross3d(zAxis, -xAxis) == -yAxis);
	assert(math_utils::cross3d(zAxis, -yAxis) == xAxis);

	assert(math_utils::cross3d(xAxis, xAxis) == origin);
}

static void unitTest_Vec3_increment_vec()
{
	Vec3 a = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 b = Vec3(0.0f, 1.0f, 1.0f);
	a += b;
	assert(a.x = 1.0f);
	assert(a.y = 1.0f);
	assert(a.z = 1.0f);
}

static void unitTest_Vec3_decrement_vec()
{
	Vec3 a = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 b = Vec3(0.0f, 1.0f, 1.0f);
	a -= b;
	assert(a.x = 1.0f);
	assert(a.y = -1.0f);
	assert(a.z = -1.0f);
}



void unitTest_Vec3()
{
	unitTest_Vec3_defaultConstructor();
	unitTest_Vec3_paramConstructor();
	unitTest_Vec3_copyConstructor();
	unitTest_Vec3_math();
	unitTest_Vec3_increment_vec();
	unitTest_Vec3_decrement_vec();
}