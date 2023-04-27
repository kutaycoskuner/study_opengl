#include "../abstract/vector.h"

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
	float dp = math_utils::dotProduct(hor, ver);
	assert(dp == 0);
	ver = (1, 5, 0);
	hor = (-1, -5, 0);
	dp = math_utils::dotProduct(hor, ver);
	assert(dp == -1 * hor.length() * ver.length());
}

void unitTest_Vec3()
{
	unitTest_Vec3_defaultConstructor();
	unitTest_Vec3_paramConstructor();
	unitTest_Vec3_copyConstructor();
	unitTest_Vec3_math();
}