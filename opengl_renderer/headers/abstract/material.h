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
	int diffuse_map_id;
	int normal_map_id;
	int specular_map_id;

	// default constructor
	Material() :
		ambient(0.0f, 0.0f, 0.0f),
		diffuse(0.0f, 0.0f, 0.0f),
		specular(0.0f, 0.0f, 0.0f),
		shininess(0.0f)
		,diffuse_map_id(-1)
		,normal_map_id(-1)
		,specular_map_id(-1)


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
		, diffuse_map_id(-1)
		, normal_map_id(-1)
		, specular_map_id(-1)
	{}
};

