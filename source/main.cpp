// ------------------------------------------------------------------------------------------------
//				Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/renderer.h"
#include "../headers/core/openGL.h"
#include "../headers/test/basic.h"
#include "../headers/utils/utilities.h"
#include <iostream>
#include <unordered_map>

// ------------------------------------------------------------------------------------------------
//				Main
// ------------------------------------------------------------------------------------------------
int main()
{
	// get config
	Renderer::ConfigData config;
	std::string path_mode = "relative";

	//std::cout << "trying to load config from artifacts path." << std::endl;
	config = file_utils::parseSimple(file_utils::getExecutableDir() + std::string("/config/config.yaml"));

	if (config.empty())
	{
		//std::cout << "failed to open artifacts configurations." << std::endl;
		//std::cout << "trying to load config from preprocessor directive path." << std::endl;
		config = file_utils::parseSimple(CONFIG_DIR_FULL + std::string("config.yaml"));
		;
		path_mode = "full";
	}

	if (config.empty())
	{
		std::cout << "failed to open configuration file." << std::endl;
		return 0;
	}

	// blackboarding: blank feature testing
	if (config.at("blackboard").at("is_blackboard") == "true")
	{
		blackboard();
		return 0;
	}

	// unit, integration test
	test();

	// instantiate
	Renderer app;

	// start program
	app.initialize(config);

	app.setPathType(path_mode);

	// main application loop
	while (app.reload)
	{
		app.reload = false;
		app.load(config);
		app.mainLoop(config);
		app.unload();
	}

	// exit the program
	int exit_code = app.exit();
	return exit_code;
}