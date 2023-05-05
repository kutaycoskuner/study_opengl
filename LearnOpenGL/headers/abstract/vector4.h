#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "vector.h"
#include <cmath>

// ----- abstract declarations

// ----- function declarations

// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	// default constructor
	Vec4() :x(0), y(0), z(0), w(0) {}
	// parameter constructors
	Vec4(float p_x, float p_y, float p_z, float p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}
	Vec4(const Vec3& v, const float& p_w) : x(v.x), y(v.y), z(v.z), w(p_w) {}
	Vec4(float p_x) : x(p_x), y(p_x), z(p_x), w(p_x) {}
	// copy constructor
	Vec4(const Vec4& vec) :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	// negation
	Vec4 operator-() const
	{
		return { -x, -y, -z, -w };
	}

	// vec + vec
	Vec4 operator+(const Vec4& other) const
	{
		Vec4 result = {
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w
		};
		return result;
	}

	// vec - vec
	Vec4 operator-(const Vec4& other) const
	{
		Vec4 result = {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w
		};
		return result;
	}

	// vec + scalar
	Vec4 operator+(const float& other) const
	{
		Vec4 result = {
			x + other,
			y + other,
			z + other,
			w + other
		};
		return result;
	}

	// vec - scalar
	Vec4 operator-(const float& other) const
	{
		Vec4 result = {
			x - other,
			y - other,
			z - other,
			w - other
		};
		return result;
	}

	// ==
	bool operator==(const Vec4& other) const
	{
		if (x != other.x) return false;
		if (y != other.y) return false;
		if (z != other.z) return false;
		if (w != other.w) return false;
		return true;
	}

	// dot
	float dot(const Vec4& other) const
	{
		float result = x * other.x + y * other.y + z * other.z + w * other.w;
		return result;
	}

	// length
	float length() const
	{
		float result = sqrtf(x * x + y * y + z * z + w * w);
		return result;
	}

	// normalize
	void normalize()
	{
		float len = this->length();
		*this = { x / len, y / len, z / len, w / len };
	}

	// normalized
	Vec4 normalized() const
	{
		float len = this->length();
		Vec4 result = { x / len, y / len, z / len, w / len };
		return result;
	}

};

// ------------------------------------------------------------------------------------------------
// ----- function definitions
// ------------------------------------------------------------------------------------------------

