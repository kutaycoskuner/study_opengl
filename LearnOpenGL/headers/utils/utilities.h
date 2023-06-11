#pragma once

#include "../../headers/abstract/matrix4.h"
#include <string>
#include <vector>
#include<unordered_map>

struct Vec3;


namespace str_utils
{
	std::vector<std::string> split(const std::string& str, const std::string& delimiter);
}

namespace file_utils
{
	std::string readFileContents(const std::string& path);
	std::vector<std::string> parseFileToRowArray(const std::string& path);
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parseSimple(const std::string& path);
}

namespace math_utils
{ 
	constexpr float PI = 3.14159265359f;
	// scaling
	float scaleByteToZeroOne(unsigned int byte);
	// trigonometri
	float radian(float degree);
	float degree(float radian);
	// float
	bool compareApprox(const float& a, const float& b);
	// vector
	std::vector<float> scaleByteToZeroOneVec3(const unsigned int x, const unsigned int y, const unsigned int z);
	std::vector<float> scaleByteToZeroOneVec3(const float x, const float y, const float z);
	float dot3d(const Vec3& v1, const Vec3& v2);
	Vec3 cross3d(const Vec3& v1, const Vec3& v2);

}

namespace mat_utils
{
	Mat4 identity4();
	Mat4 scale(const float& x, const float& y, const float& z);
	Mat4 scale(const Vec3& vec);
	Mat4 scale(const float& x);
	Mat4 translation(const float& x, const float& y, const float& z);
	Mat4 translation(const float& x);
	Mat4 translation(const Vec3& vec);
	Mat4 rotationX(const float& angleInRadians);
	Mat4 rotationY(const float& angleInRadians);
	Mat4 rotationZ(const float& angleInRadians);
	Mat4 rotationXYZ(const float& angleInRadians, const Vec3& axis);
	Mat4 projectPerspective(float fov_inRadians, float aspect_ratio, float near, float far);
	Mat4 projectPerspective(float near, float far, float left, float right, float top, float bottom);
}

namespace img_utils
{
	unsigned int createTexture(const std::string& path, const int& wrapping = 0);
	void setVerticalFlipMode(bool flipMode);
}