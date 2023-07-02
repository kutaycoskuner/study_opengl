// ----- libs
#include "../../headers/abstract/vector4.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

// ---- self names
using namespace math_utils;

// ----- tests

// default constructor
static void unitTest_Vec4_defaultConstructor()
{
	Vec4 vec;
	assert(vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f && vec.w == 0.0f);
}

// param consturctor
static void unitTest_Vec4_paramConstructor()
{
	Vec4 vec1(1, 0, 1, 1);
	assert(vec1.x == 1.0f && vec1.y == 0.0f && vec1.z == 1.0f && vec1.w == 1.0f);
	float param = 3.6f;
	Vec4 vec2(param);
	assert(vec2.x == param && vec2.y == param && vec2.z == param && vec2.w == param);
}

// copy constructor
static void unitTest_Vec4_copyConstructor()
{
	Vec4 vec_toCopy(1, 5, 12, 3.2);
	Vec4 vec(vec_toCopy);
	assert(
		compareApprox(vec.x, 1.0f) &&
		compareApprox(vec.y, 5.0f) &&
		compareApprox(vec.z, 12.0f) &&
		compareApprox(vec.w, 3.2f)
	);
}

// math negation
static void unitTest_Vec4_negation()
{
	Vec4 vec_toNegate(-5, 4, 23, 1);
	Vec4 vec = -vec_toNegate;
	assert(
		compareApprox(vec.x, 5)		&&
		compareApprox(vec.y, -4)	&&
		compareApprox(vec.z, -23)	&&
		compareApprox(vec.w, -1)
	);
}

// math vec-vec addition
static void unitTest_Vec4_addition()
{
	Vec4 vec1 (-5, 4, 23, 1);
	Vec4 vec2 (-4, 23, 6, -5);
	Vec4 vec = vec1 + vec2;
	assert(
		compareApprox(vec.x, -9) &&
		compareApprox(vec.y, 27) &&
		compareApprox(vec.z, 29) &&
		compareApprox(vec.w, -4)
	);
}

// math vec-vec subtraction
static void unitTest_Vec4_subtraction()
{
	Vec4 vec1(-5, 4, 23, 1);
	Vec4 vec2(-4, 23, 6, -5);
	Vec4 vec = vec1 - vec2;
	assert(
		compareApprox(vec.x,  -1) &&
		compareApprox(vec.y, -19) &&
		compareApprox(vec.z,  17) &&
		compareApprox(vec.w,   6)
	);
}

// math vec-ska addition
static void unitTest_Vec4_addition_skalar()
{
	Vec4 vec1(-5, 4, 23, 1);
	float ska = 3;
	Vec4 vec = vec1 + ska;
	assert(
		compareApprox(vec.x, -2) &&
		compareApprox(vec.y,  7) &&
		compareApprox(vec.z, 26) &&
		compareApprox(vec.w,  4)
	);
}

// math vec-ska subtraction
static void unitTest_Vec4_subtraction_skalar()
{
	Vec4 vec1(-5, 4, 23, 1);
	float ska = 3;
	Vec4 vec = vec1 - ska;
	assert(
		compareApprox(vec.x, -8) &&
		compareApprox(vec.y,  1) &&
		compareApprox(vec.z, 20) &&
		compareApprox(vec.w, -2)
	);
}

// length
static void unitTest_Vec4_length()
{
	Vec4 vec1(2, 3, 4, 5);
	assert(
		compareApprox(vec1.length(), 7.348469f)
	);
}

// normalization
static void unitTest_Vec4_normalization()
{
	Vec4 vec(2.0f, 3.0f, 4.0f, 5.0f);
	vec.normalize();
	constexpr float len = 7.348469f;
	constexpr float x = 2.0f / len;
	constexpr float y = 3.0f / len;
	constexpr float z = 4.0f / len;
	constexpr float w = 5.0f / len;
	assert(
		compareApprox(vec.x, x),
		compareApprox(vec.y, y),
		compareApprox(vec.z, z),
		compareApprox(vec.w, w)
	);
}

// normalized
static void unitTest_Vec4_normalized()
{
	Vec4 vec1(2.0f, 3.0f, 4.0f, 5.0f);
	Vec4 vec = vec1.normalized();
	constexpr float len = 7.348469f;
	const float x = vec1.x / len;
	const float y = vec1.y / len;
	const float z = vec1.z / len;
	const float w = vec1.w / len;
	assert(
		compareApprox(vec.x, x),
		compareApprox(vec.y, y),
		compareApprox(vec.z, z),
		compareApprox(vec.w, w)
	);
}

// dot
static void unitTest_Vec4_dot()
{
	Vec4 vec1(2.0f, 3.0f, 4.0f, 5.0f);
	Vec4 vec2(3.0f, 1.0f, 0.0f, 4.0f);

	float result = vec1.dot(vec2);
	assert(
		compareApprox(result, (6.0f + 3.0f + 0.0f + 20.0f))
	);
}

// unittest
void unitTest_Vec4()
{
	unitTest_Vec4_defaultConstructor();
	unitTest_Vec4_paramConstructor();
	unitTest_Vec4_copyConstructor();
	unitTest_Vec4_negation();
	unitTest_Vec4_addition();
	unitTest_Vec4_subtraction();
	unitTest_Vec4_addition_skalar();
	unitTest_Vec4_subtraction_skalar();
	unitTest_Vec4_length();
	unitTest_Vec4_normalization();
	unitTest_Vec4_normalized();
	unitTest_Vec4_dot();
}