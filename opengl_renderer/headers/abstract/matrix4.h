#pragma once
// ------------------------------------------------------------------------------------------------
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "vector3.h"
#include "vector4.h"
#include <array>

// ------------------------------------------------------------------------------------------------
// ----- abstract declarations
// ------------------------------------------------------------------------------------------------
struct Mat4;

// ------------------------------------------------------------------------------------------------
// ----- function declerations
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
struct Mat4
{
	// parameters
	union
	{
		Vec4 r[4]; // row
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	// default constructor
	Mat4()
		: _11(1), _12(0), _13(0), _14(0)
		, _21(0), _22(1), _23(0), _24(0)
		, _31(0), _32(0), _33(1), _34(0)
		, _41(0), _42(0), _43(0), _44(1)
	{}
	// parameter constructor
	Mat4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
		: _11(m11), _12(m12), _13(m13), _14(m14)
		, _21(m21), _22(m22), _23(m23), _24(m24)
		, _31(m31), _32(m32), _33(m33), _34(m34)
		, _41(m41), _42(m42), _43(m43), _44(m44)
	{}
	Mat4(float val)
		: _11(val), _12(val), _13(val), _14(val)
		, _21(val), _22(val), _23(val), _24(val)
		, _31(val), _32(val), _33(val), _34(val)
		, _41(val), _42(val), _43(val), _44(val)
	{}
	// copy constructor
	Mat4(const Mat4& other)
		: _11(other._11), _12(other._12), _13(other._13), _14(other._14)
		, _21(other._21), _22(other._22), _23(other._23), _24(other._24)
		, _31(other._31), _32(other._32), _33(other._33), _34(other._34)
		, _41(other._41), _42(other._42), _43(other._43), _44(other._44)
	{}

	// unary -
	Mat4 operator-() const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = -m[i][j];
			}
		}
		return result;
	}

	// mat mat addition
	Mat4 operator+(const Mat4& other) const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}
		return result;
	}

	// mat mat sub
	Mat4 operator-(const Mat4& other) const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][j] - other.m[i][j];
			}
		}
		return result;
	}

	// mat scalar product
	Mat4 operator*(const float& other) const
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[i][j] * other;
			}
		}
		return result;
	}

	// mat vec product
	Vec4 operator*(const Vec4& vec) const
	{
		Vec4 result;
		result.x = vec.dot(this->r[0]);
		result.y = vec.dot(this->r[1]);
		result.z = vec.dot(this->r[2]);
		result.w = vec.dot(this->r[3]);
		return result;
	}

	// mat mat product
	Mat4 operator*(const Mat4& other) const
	{
		Mat4 result = Mat4(0.0f);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}
		return result;
	}

	// override =* 
	void operator*=(const Mat4& other)
	{
		*this = *this * other;
	}

	// transposed
	Mat4 transposed() const
	{
		Mat4 result;
		for (int ii = 0; ii < 4; ii++)
		{
			for (int jj = 0; jj < 4; jj++)
			{
				result.m[jj][ii] = m[ii][jj];
			}
		}
		return result;
	}

	const float* value_ptr()
	{
		return &m[0][0];
	}

	std::array<float, 16> copytoFloatArray() const {
		std::array<float, 16> result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result[i * 4 + j] = m[i][j];
			}
		}
		return result;
	}
};