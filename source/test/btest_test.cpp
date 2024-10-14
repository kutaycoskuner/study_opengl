// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "vector4.h"
#include "unit_tests.h"
#include "integration_tests.h"
#include "openGL.h"
#include "utilities.h"
#include "shaders.h"
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
	unitTest_Transform();
	unitTest_Queue();
}

void runIntegrationTests()
{
	integrationTest_matrixTranslations();
}

