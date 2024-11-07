// ----- Libraries
// ----------------------------------------------------------------------------
#include "data.h"     
#include "utilities.h"     

// ----- Data
// ----------------------------------------------------------------------------
DirectionalLight PredefSceneLights::d_light = {
	.position		= Vec3(10.0f, 10.0f, 0.0f)
	,.direction		= Vec3(-1.0f, -1.0f, 0.0f)
	//.position		= Vec3(10.0f, 10.0f, 10.0f)
	//,.direction		= Vec3(-1.0f, -0.8f, -0.2f)
	//,.direction		= Vec3(1.0f, -1.0f, -2.0f)
	,.ambient		= Vec3(0.08f, .08f, 0.08f)
	,.diffuse		= Vec3(0.8f, 0.8f, 0.8f)
	,.specular		= Vec3(1.0f, 1.0f, 1.0f)
	,.brightness	= 0.4f
};

PointLight PredefSceneLights::p_light = {
	.position = Vec3(0.0f, 0.0f, 0.0f)
	,.ambient = Vec3(0.05f, 0.05f, 0.05f)
	,.diffuse = Vec3(0.8f, 0.8f, 0.8f)
	,.specular = Vec3(1.0f, 1.0f, 1.0f)
	,.constant = 1.0f
	,.linear = 0.09f
	,.quadratic = 0.032f
	,.brightness = 1.0f

};

SpotLight PredefSceneLights::s_light = {
	.position = Vec3(0.0f, 6.0f, 0.0f)
	,.direction = Vec3(0.0f, -1.0f, 0.0f)
	,.ambient = Vec3(0.02f, 0.02f, 0.02f)
	,.diffuse = Vec3(0.9f, 0.9f, 0.0f)
	,.specular = Vec3(1.0f, 1.0f, 1.0f)
	,.constant = 1.0f
	,.linear = 0.09f
	,.quadratic = 0.032f
	,.cutoff = cos(math_utils::toRadian(15.0f))
	,.outer_cutoff = cos(math_utils::toRadian(20.0f))
	,.brightness = 1.0f
};