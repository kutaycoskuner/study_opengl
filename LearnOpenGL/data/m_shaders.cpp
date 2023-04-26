// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/maps/shaders.h"     

// ------------------------------------------------------------------------------------------------
// ----- Data
// ------------------------------------------------------------------------------------------------
//
//std::unordered_map<int, int> potato = 
//{
//	{2,2},
//	{3,4}
//};
const std::unordered_map<std::string, std::string> shader_mapping =
{
	{"vrtxShader",        "shaders/vrtxShader.glsl"},
	{"fragShader",        "shaders/fragShader.glsl"},
	{"fragShader_1",      "shaders/fragShader_1.glsl"},
	{"fragShader_2",      "shaders/fragShader_2.glsl"},
};
