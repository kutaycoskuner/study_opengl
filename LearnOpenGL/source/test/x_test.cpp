// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/vector.h"
#include "../headers/test/unit_tests.h"
#include "../headers/test/integration_tests.h"
#include "../headers/core/openGL.h"
#include "../headers/utils/utilities.h"
#include "../headers/maps/shaders.h"
#include <iostream>
#include <fstream>

// ------------------------------------------------------------------------------------------------
// ----- Function definitions
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ----- Function declarations
// ------------------------------------------------------------------------------------------------
void runUnitTests();
void runIntegrationTests();

// ------------------------------------------------------------------------------------------------
// ----- Function definitions
// ------------------------------------------------------------------------------------------------
int test()
{
	runUnitTests();
	runIntegrationTests();
	return EXIT_SUCCESS;
	// todo fail case gir
}

void runUnitTests()
{
	unitTest_Vec3();
	unitTest_Vec4();
	unitTest_Mat4();
}

void runIntegrationTests()
{
	integrationTest_matrixTranslations();
}

