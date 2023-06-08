// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/vector3.h"
#include "../../headers/utils/utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

// ------------------------------------------------------------------------------------------------
// ----- Functions
// ------------------------------------------------------------------------------------------------

// scaler
// ------------------------------
namespace math_utils
{
	// scaling
	float scaleByteToZeroOne(unsigned int byte)
	{
		return (float(byte) / 255.0f);
	}

	// trigonometry
	float radian(float degree)
	{
		return degree * PI / 180.0f;
	}

	float degree(float radian)
	{
		return radian * 180.0f / PI;
	}

	// vector
	std::vector<float> scaleByteToZeroOneVec3(const unsigned int x, const unsigned int y, const unsigned int z)
	{
		return { scaleByteToZeroOne(x), scaleByteToZeroOne(y), scaleByteToZeroOne(z) };
	}

	std::vector<float> scaleByteToZeroOneVec3(const float x, const float y, const float z)
	{
		return { 
			scaleByteToZeroOne(static_cast<unsigned int>(x)), 
			scaleByteToZeroOne(static_cast<unsigned int>(y)), 
			scaleByteToZeroOne(static_cast<unsigned int>(z)) 
		};
	}

	bool compareApprox(const float& a, const float& b)
	{
		const float error_threshold = 0.000001f;
		return fabsf(a - b) < error_threshold;
	}

	float dot3d(const Vec3& v1, const Vec3& v2)
	{
		float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
		return result;
	}

	Vec3 cross3d(const Vec3& v1, const Vec3& v2)
	{
		float x = v1.y * v2.z - v1.z * v2.y;
		float y = v1.z * v2.x - v1.x * v2.z;
		float z = v1.x * v2.y - v1.y * v2.x;
		return Vec3(x, y, z);
	}

}

// string manipulation
// ------------------------------
namespace str_utils
{
	void trim(std::string& str) {
		// find the first non-whitespace character
		size_t first = str.find_first_not_of(" \n\r\f\v");

		if (first == std::string::npos) {
			// if the string is all whitespace, clear it
			str.clear();
			return;
		}

		// find the last non-whitespace character
		size_t last = str.find_last_not_of(" \n\r\f\v");

		// extract the trimmed substring
		str = str.substr(first, last - first + 1);
	}

	std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
		std::vector<std::string> substrings;
		size_t start = 0;
		size_t end = 0;

		while ((end = str.find(delimiter, start)) != std::string::npos) {
			substrings.push_back(str.substr(start, end - start));
			start = end + delimiter.length();
		}
		substrings.push_back(str.substr(start));
		return substrings;
	}

	int countLeadingSpaces(const std::string& str) {
		int count = 0;
		for (char c : str) {
			if (c == ' ') {
				count += 1; // assume 4 spaces per tab
			}
			else {
				break;
			}
		}
		return count / 2;
	}
}

// read and deserialize file
// ------------------------------
std::string file_utils::readFileContents(const std::string& path)
{
	// Open the file at the given path
	std::ifstream file(path);

	// Check if the file was opened successfully
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return "";
	}

	// Read the contents of the file into an std::string
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Close the file
	file.close();

	return contents;
}

std::vector<std::string> file_utils::parseFileToRowArray(const std::string& path)
{
	std::string str = file_utils::readFileContents(path);
	std::vector<std::string> rows;
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		rows.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	// add the last row to the vector
	rows.push_back(str);
	return rows;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> file_utils::parseSimple(const std::string& path) {
	using namespace str_utils;
	std::vector<std::string> rows = parseFileToRowArray(path);
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config;
	int currentIndent = 0;
	std::string parent = "";

	for (const std::string& row : rows) {
		if (row.find(":") == std::string::npos) { continue; }
		std::vector<std::string> substrings = split(row, ":");
		// handle key
		if (substrings.empty()) { continue; }
		if (substrings[0].size() == 0) { continue; }
		trim(substrings[0]);
		// check indentation
		int space = countLeadingSpaces(substrings[0]);
		substrings[0].erase(0, space);
		//std::cout << substrings[0] << std::endl;
		// handle value
		if (substrings.size() < 2 || substrings[1] == "")
		{
			parent = substrings[0];
			config[parent];
			continue;
		}
		if (substrings[1].size() == 0) { continue; }
		trim(substrings[1]);
		config[parent][substrings[0]] = substrings[1];
		//std::cout << substrings[1] << std::endl;
	}

	//std::cout << config["SCR"]["WIDTH"]  << std::endl;

	return config;

}