// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/core/openGL.h"
#include "../headers/test/basic.h"
#include "../headers/utils/utilities.h"
#include <iostream>
#include <unordered_map>

// ------------------------------------------------------------------------------------------------
// ==== Main
// ------------------------------------------------------------------------------------------------
int main()
{
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config = file_utils::parseSimple("config/config.yaml");
	
	if (config["test"]["is_testing"] == "true")
	{
		test();
	}
	else
	{
		runApplication(config);
	}
	
	return 0;
}