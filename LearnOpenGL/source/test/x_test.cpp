// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/vector.h"
#include "../headers/test/unit_tests.h"
#include "../headers/core/openGL.h"
#include "../headers/utils/utilities.h"
#include "../headers/maps/shaders.h"
#include <iostream>
#include <fstream>

// ------------------------------------------------------------------------------------------------
// ----- Function definitions
// ------------------------------------------------------------------------------------------------
void test()
{
	unitTest_Vec3();
	unitTest_Vec4();
	unitTest_Mat4();

	//std::cout << shader_mapping.size();
	//parseSimple("config/config.yaml");
	//parseSimple();
	//std::cout<<readFileContents("settings/fragShader.glsl");
}