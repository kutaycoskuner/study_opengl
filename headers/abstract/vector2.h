#pragma once
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include <cmath>

// ----- abstract declarations

// ----- function declarations

// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
struct Vec2
{
	float x;
	float y;

	// default constructor
	Vec2() :x(0), y(0) {}
	// parameter constructors
	Vec2(float p_x, float p_y) : x(p_x), y(p_y) {}
	Vec2(float p_x) : x(p_x), y(p_x) {}
	// copy constructor
	Vec2(const Vec2& vec) :x(vec.x), y(vec.y) {}

	// float pointer converter
	float* toFloatPointer()
	{
		return &x;
	}

	// negation
	Vec2 operator-() const
	{
		return { -x, -y };
	}

	// vec + vec
	Vec2 operator+(const Vec2& other) const
	{
		Vec2 result = {
			x + other.x,
			y + other.y
		};
		return result;
	}

	// vec - vec
	Vec2 operator-(const Vec2& other) const
	{
		Vec2 result = {
			x - other.x,
			y - other.y
		};
		return result;
	}

	// vec + scalar
	Vec2 operator+(const float& other) const
	{
		Vec2 result = {
			x + other,
			y + other
		};
		return result;
	}

	// vec - scalar
	Vec2 operator-(const float& other) const
	{
		Vec2 result = {
			x - other,
			y - other
		};
		return result;
	}

	// ==
	bool operator==(const Vec2& other) const
	{
		if (x != other.x) return false;
		if (y != other.y) return false;
		return true;
	}

	// length
	float length() const
	{
		float result = sqrtf(x * x + y * y);
		return result;
	}

	// normalize
	void normalize()
	{
		float len = this->length();
		*this = { x / len, y / len };
	}

	// normalized
	Vec2 normalized() const
	{
		float len = this->length();
		Vec2 result = { x / len, y / len};
		return result;
	}

};


