// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/vector3.h"
#include "../../headers/utils/utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

// ------------------------------------------------------------------------------------------------
// ----- Functions
// ------------------------------------------------------------------------------------------------

// scaler
// ------------------------------
namespace math_utils
{
	// Performs linear interpolation between two values (a and b) based on a factor t.
	float lerp(float start, float end, float factor)
	{
		return start + factor * (end - start);
	}

	float randomFloat(float min, float max) {
		if (min > max)
		{
			float temp = min;
			min        = max;
			max        = temp;
		}
		return min + ((float)rand() / RAND_MAX) * (max - min);
	}
	// scaling
	float scaleByteToZeroOne(unsigned int byte)
	{
		return (float(byte) / 255.0f);
	}

	float scaleByteToZeroOne(float byte)
	{
		return (byte / 255.0f);
	}

	Vec3 scaleByteToZeroOne(float a, float b, float c)
	{
		return Vec3(scaleByteToZeroOne(float(a)), 
					scaleByteToZeroOne(float(b)), 
					scaleByteToZeroOne(float(c))
		);
	}

	Vec3 scaleByteToZeroOne(unsigned int a, unsigned int b, unsigned int c)
	{
		return scaleByteToZeroOne(float(a), float(b), float(c));
	}


	// trigonometry
	float toRadian(float degree)
	{
		return degree * PI / 180.0f;
	}

	float toDegree(float radian)
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
		// Standard cross product calculation
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
namespace file_utils {
	std::string getExecutableDir() {
		char path[MAX_PATH];
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule != NULL) {
			GetModuleFileName(hModule, path, sizeof(path));
		}
		std::filesystem::path exePath(path);
		return exePath.parent_path().string(); // Get the directory of the executable
	}
	// Utility function to return the file name from a path
	std::string getFileNameWithoutExtension(const std::string& filePath) {
		return fs::path(filePath).filename().string();
	}

	// Utility function to return the last directory name from a path
	std::string getDirectoryName(const std::string& filePath) {
		fs::path path = fs::path(filePath).parent_path();  // Get parent path
		return path.filename().string();  // Get the last folder name
	}

	// Utility function to return the full directory path without the file name
	std::string getDirectoryPath(const std::string& filePath) {
		return fs::path(filePath).parent_path().string();
	}

	// Utility function to return the file extension
	std::string getExtension(const std::string& filePath) {
		return fs::path(filePath).extension().string();
	}
}

std::string file_utils::readFileContents(const std::string& path)
{
	// Open the file at the given path
	std::ifstream file(path);

	// Check if the file was opened successfully
	if (!file.is_open()) {
		std::cerr << "failed to open file: " << path << std::endl;
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

namespace color_utils
{
	unsigned int hexToUInt(const std::string& hex) {
		std::istringstream stream(hex);
		unsigned int intValue;
		stream >> std::hex >> intValue;
		return intValue;
	}

	std::vector<unsigned int> hexToRGB(const std::string& hexColor) {
		std::vector<unsigned int> result;

		// test #121212 to 18, 18, 18
		// test #a153bb to 161, 83, 187

		// Remove '#' if present
		std::string color = (hexColor[0] == '#') ? hexColor.substr(1) : hexColor;

		// Split the hex color code into pairs of characters
		std::vector<std::string> hexPairs;
		for (size_t i = 0; i < color.length(); i += 2) {
			hexPairs.push_back(color.substr(i, 2));
		}

		// Convert each pair to byte values
	// Convert each pair to byte values
		for (const std::string& hexPair : hexPairs) {
			result.push_back(hexToUInt(hexPair));
		}


		return result;
	}

	//std::vector<unsigned int> hexToFloatRGB(const std::string& hexColor)
}