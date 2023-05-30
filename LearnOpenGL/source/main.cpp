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
	Application::c_configType config = file_utils::parseSimple("config/config.yaml");


	// check if testing
	if (config.at("test").at("is_testing") == "true")
		return test();

	// instantiate
	Application app;

	// run program
	app.Initialize(config);
	app.Load(config);
	app.MainLoop();
	app.Unload();
	int exit_code = app.Exit();

	return exit_code;
}