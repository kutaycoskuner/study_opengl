// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/matrix.h"
#include "../../headers/abstract/vector.h"
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

	Mat4 rotationXYZ(const float& angleInRadians, const Vec3& axis)
	{
		const float cos = cosf(angleInRadians);
		const float sin = sinf(angleInRadians);
		const float one_minus_cos = 1 - cos;
		const float& omc = one_minus_cos;
		const Vec3& r = axis;
		assert(math_utils::compareApprox(axis.length(), 1.0f));
		return Mat4(
			cos+r.x*r.x*omc,     r.x*r.y*omc-r.z*sin, r.x*r.z*omc+r.y*sin, 0,
			r.y*r.x*omc+r.z*sin, cos+r.y*r.y*omc,	  r.y*r.z*omc-r.x*sin, 0,
			r.y*r.x*omc+r.y*sin, r.z*r.y*omc+r.x*sin, cos+r.z*r.z*omc,     0,
			0,					 0,					  0,				   1
		);
	}

	//Mat4 transpose(const Mat4& mat)
	//{
	//	// [0][1] [1][0]
	//	// [0][2] [2][0]

	//	for (int ii = 0; ii < 4; ii++)
	//	{
	//	}
	//}

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
		const float t = near * std::tan(fov_inRadians / 2);
		const float b = -t;
		const float r = aspect_ratio * t;
		const float l = -r;
		const float n = near;
		const float f = far;
		return projectPerspective(n, f, l, r, t, b);
	}

	//Mat4 projectOrthographic()
	//{}


}