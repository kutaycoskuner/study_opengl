#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include <cassert>
#include <cmath>

struct Vec3;

// ------------------------------------------------------------------------------------------------
// ----- function declarations
// ------------------------------------------------------------------------------------------------

namespace math_utils
{
	bool compareApprox(const float& a, const float& b);
	float dot3d(const Vec3& v1, const Vec3& v2);
	Vec3 cross3d(const Vec3& v1, const Vec3& v2);
}


// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
struct Vec3
{
	float x;
	float y;
	float z;

	// default constructor
	Vec3() :x(0), y(0), z(0) {}
	// parameter constructior
	Vec3(float in_x, float in_y, float in_z) :x(in_x), y(in_y), z(in_z) {}
	Vec3(float in_x) :x(in_x), y(in_x), z(in_x) {}
	// copy constructor
	Vec3(const Vec3& vec) :x(vec.x), y(vec.y), z(vec.z) {}

	// math
	// ------------------------------
	// unary
	Vec3 operator-() const
	{
		return { -x, -y, -z };
	}
	// vector vector + 
	Vec3 operator+(const Vec3& other) const
	{
		Vec3 result = { x + other.x, y + other.y, z + other.z };
		return result;
	}

	// vector vector - 
	Vec3 operator-(const Vec3& other) const
	{
		Vec3 result = { x - other.x, y - other.y, z - other.z };
		return result;
	}

	// scalar vector +
	Vec3 operator+(const float& other) const
	{
		Vec3 result = { x + other, y + other, z + other };
		return result;
	}

	// scalar vector -
	Vec3 operator-(const float& other) const
	{
		Vec3 result = { x - other, y - other, z - other };
		return result;
	}

	// 
	bool operator==(const Vec3& other) const
	{
		if (x != other.x) return false;
		if (y != other.y) return false;
		if (z != other.z) return false;
		return true;
	}

	float dot(const Vec3& other) const
	{
		float result = math_utils::dot3d(*this, other);
		return result;
	}

	// length
	float length() const
	{
		float result = sqrtf(x * x + y * y + z * z);
		return result;
	}

	void normalize() 
	{
		float len = this->length();
		*this = { x / len, y / len, z / len };
	}

	Vec3 normalized() const
	{
		float len = this->length();
		Vec3 result = { x / len, y / len, z / len };
		return result;
	}
};

// ------------------------------------------------------------------------------------------------
// ----- function definitions
// ------------------------------------------------------------------------------------------------


//template<class T>
//static float length(T vec)
//{
//	return vec.length();
//}

