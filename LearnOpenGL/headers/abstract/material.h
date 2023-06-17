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
struct Material
{

	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	float shininess;

	// default constructor
	Material() :
		ambient(0.0f, 0.0f, 0.0f),
		diffuse(0.0f, 0.0f, 0.0f),
		specular(0.0f, 0.0f, 0.0f),
		shininess(0.0f)
	{}
	// parameter constructor
	Material(
		float ambientX, float ambientY, float ambientZ, 
		float diffuseX, float diffuseY, float diffuseZ, 
		float specularX, float specularY, float specularZ, 
		float shininess_val
		):
		ambient(ambientX, ambientY, ambientZ), 
		diffuse(diffuseX, diffuseY, diffuseZ), 
		specular(specularX, specularY, specularZ),		
		shininess(shininess_val)
	{}
};

