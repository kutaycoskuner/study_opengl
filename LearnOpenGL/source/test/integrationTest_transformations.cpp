// libs
#include "../../headers/abstract/matrix.h"
#include "../../headers/abstract/vector.h"
#include "../../headers/abstract/vector4.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

// self keys
using namespace math_utils;
using namespace mat_utils;

// pre

// functions
static void integrationTest_transformations()
{
	Vec3 v(0.0f, 0.0f, 0.0f);
	Vec4 point(v, 1.0f);
	Mat4 translation_matrix = translation(1.0f, 2.0f, 3.0f);
	Vec4 v_translated = translation_matrix * point;
	assert(
		compareApprox(v_translated.x, 1.0f) &&
		compareApprox(v_translated.y, 2.0f) &&
		compareApprox(v_translated.z, 3.0f) &&
		compareApprox(v_translated.w, 1.0f)
	);
}

static void integrationTest_scale()
{
	Vec4 v(1.0f, 1.0f, 1.0f, 1.0f);
	Mat4 scale_matrix = scale(1.0f, 2.0f, 3.0f);
	Vec4 v_transformed = scale_matrix * v;
	assert(
		compareApprox(v_transformed.x, 1.0f) &&
		compareApprox(v_transformed.y, 2.0f) &&
		compareApprox(v_transformed.z, 3.0f) &&
		compareApprox(v_transformed.w, 1.0f)
	);
}

static void integrationTest_rotationX()
{
	Vec4 v(0.0f, 1.0f, 0.0f, 1.0f);
	Mat4 transformation_matrix = rotationX(PI/2);
	Vec4 v_transformed = transformation_matrix * v;
	assert(
		compareApprox(v_transformed.x, 0.0f) &&
		compareApprox(v_transformed.y, 0.0f) &&
		compareApprox(v_transformed.z, 1.0f) &&
		compareApprox(v_transformed.w, 1.0f)
	);
}

static void integrationTest_rotationY()
{
	Vec4 v(1.0f, 1.0f, 1.0f, 1.0f);
	Mat4 transformation_matrix = rotationY(PI / 2);
	Vec4 v_transformed = transformation_matrix * v;
	assert(
		compareApprox(v_transformed.x, 1.0f)	&&
		compareApprox(v_transformed.y, 1.0f)	&&
		compareApprox(v_transformed.z, -1.0f)	&&
		compareApprox(v_transformed.w, 1.0f)
	);
}

static void integrationTest_rotationZ()
{
	Vec4 v(-3.0f, 2.0f, 1.0f, 1.0f);
	Mat4 transformation_matrix = rotationZ(PI / 2);
	Vec4 v_transformed = transformation_matrix * v;
	assert(
		compareApprox(v_transformed.x, -2.0f) &&
		compareApprox(v_transformed.y, -3.0f) &&
		compareApprox(v_transformed.z, 1.0f) &&
		compareApprox(v_transformed.w, 1.0f)
	);
}

static void integrationTest_rotationXYZ()
{
	Vec4 v(2.0f, -4.0f, 6.0f, 1.0f);
	Vec3 rotation_axis = Vec3(1.0f, 0.0f, 0.0f).normalized();
	Mat4 transformation_matrix = rotationXYZ(PI / 2, rotation_axis);
	Vec4 v_transformed = transformation_matrix * v;
	assert(
		compareApprox(v_transformed.x, 2.0f) &&
		compareApprox(v_transformed.y, -6.0f) &&
		compareApprox(v_transformed.z, -4.0f) &&
		compareApprox(v_transformed.w, 1.0f)
	);
}

static void integrationTest_combined()
{
	Vec4 v(1.0f, 1.0f, 1.0f, 1.0f);
	Mat4 scale_matrix = scale(2.0f, 3.0f, 4.0f);
	Vec4 result = scale_matrix * v;
	
	Mat4 rotate_matrix = rotationY(-PI / 2);
	result = rotate_matrix * result;

	Mat4 trans_matrix = translation(2.0f, 2.0f, 2.0f);

	result = trans_matrix * result;
	
	Mat4 transformation_matrix = trans_matrix * rotate_matrix * scale_matrix;
	result = transformation_matrix * v;
	assert(
		compareApprox(result.x, -2.0f) &&    // 2.0f // -4.0  // -2
		compareApprox(result.y,  5.0f) &&    // 3.0f //  3.0  //  5
		compareApprox(result.z,  4.0f) &&    // 4.0f //  2.0  //  4
		compareApprox(result.w,  1.0f)
	);
}


void integrationTest_matrixTranslations()
{
	integrationTest_transformations();
	integrationTest_scale();
	integrationTest_rotationX();
	integrationTest_rotationY();
	integrationTest_rotationZ();
	integrationTest_rotationXYZ();
	integrationTest_combined();
}