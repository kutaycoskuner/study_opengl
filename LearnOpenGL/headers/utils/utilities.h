#pragma once
#include <string>
#include <vector>
#include<unordered_map>

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
	float scaleByteToZeroOne(unsigned int byte);
	std::vector<float> scaleByteToZeroOneVec3(const unsigned int x, const unsigned int y, const unsigned int z);
	std::vector<float> scaleByteToZeroOneVec3(const float x, const float y, const float z);


}

namespace img_utils
{
	unsigned int createTexture(const std::string& path, const int& wrapping = 0);
	void setVerticalFlipMode(bool flipMode);
}