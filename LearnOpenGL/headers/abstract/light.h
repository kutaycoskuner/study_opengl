#pragma once
#pragma once
// ----- libraries
// ----------------------------------------------------------------------------
#include "../abstract/vector3.h"

// ----- forward declarations
// ----------------------------------------------------------------------------

// ----- function declarations
// ----------------------------------------------------------------------------

// ----- abstract
// ----------------------------------------------------------------------------
struct Light
{
	// will be removed as it will not be necessary on directional light model
	Vec3 position;
	Vec3 direction;
	
	Vec3 color;
	float brightness;

	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;

	float constant;
	float linear;
	float quadratic;
};