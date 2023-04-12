#pragma once
#ifndef S_SHADER
#define S_SHADER


#include <string>

struct ShaderData
{
	// variables
	// -----------------------------------
	const std::string name;
	const std::string path;
	const std::string content;

	// constructors
	// -----------------------------------	
	// Default constructor
	ShaderData() : name(""), path(""), content("") {}

	// Parameter constructor
	ShaderData(const std::string& name, const std::string& path, const std::string& content) 
		: name(name), path(path), content(content) {}

	// Copy constructor
	ShaderData(const ShaderData& other) : name(other.name), path(other.path), content(other.content) {}

	// todo move constructor

	// todo destructor
};

#endif
