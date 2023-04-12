#pragma once
#include <string>
#include <vector>
#include<unordered_map>
// string manipulation
std::vector<std::string> split(const std::string& str, const std::string& delimiter);
// read write
std::string readFileContents(const std::string& path);
std::vector<std::string> parseFileToRowArray(const std::string& path);
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parseSimple(const std::string& path);

// scale
inline float scaleByteToZeroOne(unsigned int byte) { return (float(byte) / 255.0f); }
