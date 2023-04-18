// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/core/openGL.h"
#include "../headers/test/basic.h"
#include "../headers/utilities/utilities.h"
#include <iostream>
#include <unordered_map>

// ------------------------------------------------------------------------------------------------
// ==== Main
// ------------------------------------------------------------------------------------------------
int main()
{
	// configurations
	// --------------------------
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config = parseSimple("config/config.yaml");
	
	// :: test or run?
	// --------------------------
	if (config["test"]["is_testing"] == "true")
	{
		test();
	}
	else
	{
		learnOpenGL(config);
	}
	
	// :: return
	// --------------------------
	return 0;
}