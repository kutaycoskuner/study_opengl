// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/application.h"
#include "../headers/core/openGL.h"
#include "../headers/test/basic.h"
#include "../headers/utils/utilities.h"
#include <iostream>
#include <unordered_map>

// ------------------------------------------------------------------------------------------------
// ----- Main
// ------------------------------------------------------------------------------------------------
int main()
{
	// get config
	Application::ConfigData config;
	std::string path_mode = "relative";

	std::cout << "trying to load config from artifacts path." << std::endl;
	config = file_utils::parseSimple(file_utils::getExecutableDir() + std::string("/config/config.yaml"));

	if (config.empty())
	{
		std::cout << "failed to open artifacts configurations." << std::endl;
		std::cout << "trying to load config from preprocessor directive path." << std::endl;
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
	Application app;

	// run program
	app.initialize(config);

	if (path_mode == "full") app.path_mode = Application::PathMode::FULL;
	if (app.path_mode == Application::PathMode::FULL)
	{
		app.data_dir_path	= DATA_DIR_FULL;
		app.config_dir_path = CONFIG_DIR_FULL;
		app.shader_dir_path = SHADER_DIR_FULL;
	}
	else
	{
		app.data_dir_path	= file_utils::getExecutableDir() + "\\data\\";
		app.config_dir_path = file_utils::getExecutableDir() + "\\config\\";
		app.shader_dir_path = file_utils::getExecutableDir() + "\\shaders\\";
	}

	// std::cout << "Config Path: " << app.config_dir_path << std::endl;
	// std::cout << "Data Path: "	 << app.data_dir_path	<< std::endl;
	// std::cout << "Shader Path: " << app.shader_dir_path << std::endl;

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