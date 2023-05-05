// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/matrix.h"
#include "../../headers/abstract/vector.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

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
}
