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
	Application::ConfigData config = file_utils::parseSimple("config/config.yaml");
	
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