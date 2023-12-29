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
// ==== Main
// ------------------------------------------------------------------------------------------------
int main()
{
	// get config 
	Application::k_configType config = file_utils::parseSimple("config/config.yaml");

	// unit, integration test
	test();

	// instantiate
	Application app;

	// run program
	app.initialize(config);
	app.load(config);
	app.mainLoop();
	app.unload();
	int exit_code = app.exit();

	return exit_code;
}