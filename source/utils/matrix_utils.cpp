// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/matrix4.h"
#include "../../headers/abstract/vector4.h"
#include "../../headers/utils/utilities.h"
#include <cassert>
#include <cmath>

// ------------------------------------------------------------------------------------------------
// ----- Function Definitions
// ------------------------------------------------------------------------------------------------
namespace mat_utils
{
	Mat4 identity4()
	{
		return Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

	}

	Mat4 scale(const float& x, const float& y, const float& z)
	{
		return Mat4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	Mat4 scale(const Vec3& vec)
	{
		return scale(vec.x, vec.y, vec.z);
	}

	Mat4 scale(const float& x)
	{
		return scale(x, x, x);
	}

	Mat4 translation(const float& x, const float& y, const float& z)
	{
		return Mat4(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		);
	}

	Mat4 translation(const float& x)
	{
		return translation(x, x, x);
	}

	Mat4 translate(const Vec3& vec)
	{
		return translation(vec.x, vec.y, vec.z);
	}

	Mat4 translate(const float& x, const float& y, const float& z)
	{
		return Mat4(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		);
	}

	Mat4 translate(const float& x)
	{
		return translation(x, x, x);
	}

	Mat4 translation(const Vec3& vec)
	{
		return translation(vec.x, vec.y, vec.z);
	}

	Mat4 rotationX(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			1,	0,		0,		0,
			0,	cos,	-sin,	0,
			0,	sin,	cos,	0,
			0,	0,		0,		1
		);
	}

	Mat4 rotateX(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			1, 0, 0, 0,
			0, cos, -sin, 0,
			0, sin, cos, 0,
			0, 0, 0, 1
		);
	}

	Mat4 rotationY(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			cos,	0,		sin,	0,
			0,		1,		0,		0,
			-sin,	0,		cos,	0,
			0,		0,		0,		1
		);
	}

	Mat4 rotateY(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			cos, 0, sin, 0,
			0, 1, 0, 0,
			-sin, 0, cos, 0,
			0, 0, 0, 1
		);
	}
	
	Mat4 rotationZ(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			cos,	-sin,	0,		0,
			sin,	cos,	0,		0,
			0,		0,		1,		0,
			0,		0,		0,		1
		);
	}

	Mat4 rotateZ(const float& angleInRadians)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		return Mat4(
			cos, -sin, 0, 0,
			sin, cos, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Mat4 rotationXYZ(const float& angleInRadians, const Vec3& axis)
	{
		//if () // todo: normalized degilse normalalized yap 
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		const float one_minus_cos = 1 - cos;
		const float& omc = one_minus_cos;
		const Vec3& r = axis;
		assert(math_utils::compareApprox(axis.length(), 1.0f));
		return Mat4(
			cos+r.x*r.x*omc,		r.x*r.y*omc-r.z*sin,	r.x*r.z*omc+r.y*sin,	0,
			r.y*r.x*omc+r.z*sin,	cos+r.y*r.y*omc,		r.y*r.z*omc-r.x*sin,	0,
			r.z*r.x*omc-r.y*sin,	r.z*r.y*omc+r.x*sin,	cos+r.z*r.z*omc,		0,
			0,						0,						0,						1
		);
	}

	Mat4 rotateXYZ(const float& angleInRadians, const Vec3& axis)
	{
		//if () // todo: normalized degilse normalalized yap 
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		const float one_minus_cos = 1 - cos;
		const float& omc = one_minus_cos;
		const Vec3& r = axis;
		assert(math_utils::compareApprox(axis.length(), 1.0f));
		return Mat4(
			cos + r.x * r.x * omc, r.x * r.y * omc - r.z * sin, r.x * r.z * omc + r.y * sin, 0,
			r.y * r.x * omc + r.z * sin, cos + r.y * r.y * omc, r.y * r.z * omc - r.x * sin, 0,
			r.z * r.x * omc - r.y * sin, r.z * r.y * omc + r.x * sin, cos + r.z * r.z * omc, 0,
			0, 0, 0, 1
		);
	}

	Mat4 transpose(const Mat4& matrix)
	{
		Mat4 result;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[j][i] = matrix.m[i][j];
			}
		}

		return result;
	}

	//Mat4 transpose(const Mat4& mat)
	//{
	//	// [0][1] [1][0]
	//	// [0][2] [2][0]

	//	for (int ii = 0; ii < 4; ii++)
	//	{
	//	}
	//}

	Mat4 lookAtTarget(const Vec3& position, const Vec3& target, const Vec3& world_up)
	{
		// Calculate the forward (z) axis of the camera (bastaki eksi sag elden eksinin forward olusundaan geliyor.)
		Vec3 direction = -(target - position).normalized();

		// Calculate the right (x) axis by taking the cross product of world_up and forward
		Vec3 right = math_utils::cross3d(direction, world_up);

		// edge case: if two vectors are collinear then use +x as right vector.
		right = (right.length() == 0.0f)
			? Vec3(1.0f, 0.0f, 0.0f)
			: right.normalized();

		// Recalculate the orthogonal up vector (y axis)
		Vec3 up = math_utils::cross3d(right, direction);

		//return Mat4(
		//	right.x,	right.y,	right.z,	-position.x,
		//	world_up.x, world_up.y, world_up.z, -position.y,
		//	forward.x,  forward.y,  forward.z,  -position.z,
		//	0.0f,		0.0f,		0.0f,		1.0f
		//);

		// column major
		return Mat4(
			right.x,	 right.y,		right.z,	 -right.dot(position),
			up.x,		 up.y,			up.z,		 -up.dot(position),
			direction.x, direction.y,	direction.z, -direction.dot(position),
			0.0f,		 0.0f,		    0.0f,	     1.0f
		);

		// row major
		return Mat4(
			right.x,			  up.x,				 direction.x,			   0.0f,
			right.y,			  up.y,				 direction.y,			   0.0f,
			right.z,			  up.z,				 direction.z,			   0.0f,
			-right.dot(position), -up.dot(position), -direction.dot(position), 1.0f
		);
	}

	Mat4 lookAtDirection(const Vec3& position, const Vec3& in_direction, const Vec3& world_up)
	{
		// Normalize the direction vector to get the forward (z) axis
		Vec3 direction = -in_direction.normalized();

		// Calculate the right (x) axis as the cross product of world_up and forward
		Vec3 right = math_utils::cross3d(direction, world_up).normalized();

		// Recalculate the orthogonal up vector (y axis)
		Vec3 up = math_utils::cross3d(right, direction);

		// Construct the LookAt view matrix
		return Mat4(
			right.x,				right.y,			right.z,			-right.dot(position),
			up.x,					up.y,				up.z,				-up.dot(position),
			direction.x,			direction.y,		direction.z,		-direction.dot(position),
			0.0f,					0.0f,				0.0f,				1.0f
		);
	}


	Mat4 projectPerspective(float near, float far, float left, float right, float top, float bottom)
	{
		const float n = near;
		const float f = far;
		const float t = top;
		const float b = bottom;
		const float l = left;
		const float r = right;
		return Mat4(
			(2*n)/(r-l),	0,				(r+l)/(r-l),	0,
			0,				(2*n)/(t-b),	(t+b)/(t-b),	0,
			0,				0,				(f+n)/(n-f),	(2*f*n)/(n-f),
			0,				0,				-1,				0
		);
	}

	Mat4 projectPerspective(float fov_inRadians, float aspect_ratio, float near, float far)
	{
		const float n = near;
		const float f = far;
		const float e = 1.0f / std::tanf(fov_inRadians * 0.5f); // tan double icin tanf float icin
		return Mat4(
			e / aspect_ratio,	0.0f,				0.0f,					0.0f,
			0.0f,				e,					0.0f,					0.0f,
			0.0f,				0.0f,				(f+n)/(n-f),			(2.0f*f*n)/(n-f),
			0.0f,				0.0f,				-1.0f,					0.0f
		);
	}

	Mat4 projectOrthographic(const float& near, const float& far, const float& left, const float& right, const float& top, const float& bottom)
	{
		const float n = near;
		const float f = far;
		const float t = top;
		const float b = bottom;
		const float l = left;
		const float r = right;
		//return Mat4(
		//	2.0f / (r - l),		0.0f,				0.0f,					0.0f,
		//	0.0f,				2.0f / (t - b),		0.0f,					0.0f,
		//	0.0f,				0.0f,			    -2.0f / (f - n),		0.0f,
		//	-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n),     1.0f
		//);
		return Mat4(
			2.0f / (r - l),		0.0f,				0.0f,					-(r + l) / (r - l),
			0.0f,				2.0f / (t - b),		0.0f,					-(t + b) / (t - b),
			0.0f,				0.0f,			    -2.0f / (f - n),		-(f + n) / (f - n),
			0.0f,				0.0f,				0.0f,					1.0f
		);
	}

	Mat4 projectOrthographic(const float& vertical_size, const float& aspect_ratio, const float& near, const float& far)
	{
		const float n = near;
		const float f = far;
		const float h = vertical_size / 2.0f;  // Half height of the orthographic view
		const float w = h * aspect_ratio;      // Half width based on aspect ratio
		return Mat4(
			1.0f / w,			0.0f,				0.0f,					0.0f,
			0.0f,				1.0f / h,			0.0f,					0.0f,
			0.0f,				0.0f,				-2.0f / (f - n),		-(f + n) / (f - n),
			0.0f,				0.0f,				0.0f,					1.0f
		);
	}

}
