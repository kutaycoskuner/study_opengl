// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/openGL.h"
#include "../headers/basic.h"
#include "../headers/utilities.h"
#include <iostream>
#include <unordered_map>

// ------------------------------------------------------------------------------------------------
// ==== Main
// ------------------------------------------------------------------------------------------------
int main()
{
	// configurations
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config = parseSimple("config/config.yaml");

	constexpr bool b_Test = true;

	// :: glfw init
	// --------------------------
	if (config["test"]["is_testing"] == "true")
	{
		test();
		return 0;
	}
	
	// :: learning open gl
	// --------------------------
	learnOpenGL(config);
	return 0;
}