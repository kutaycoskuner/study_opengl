#pragma once

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
	// scaling
	float scaleByteToZeroOne(unsigned int byte);
	// float
	bool compareApprox(const float& a, const float& b);
	// vector
	std::vector<float> scaleByteToZeroOneVec3(const unsigned int x, const unsigned int y, const unsigned int z);
	std::vector<float> scaleByteToZeroOneVec3(const float x, const float y, const float z);
	float dot3d(const Vec3& v1, const Vec3& v2);
	Vec3 cross3d(const Vec3& v1, const Vec3& v2);

}

namespace img_utils
{
	unsigned int createTexture(const std::string& path, const int& wrapping = 0);
	void setVerticalFlipMode(bool flipMode);
}