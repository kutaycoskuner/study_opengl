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
    Vec3 direction;
	Vec3 position;

    Vec3 color;
    float brightness;

	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float inner_cutoff;
    float outer_cutoff;
};

struct DirectionalLight {
    
    Vec3 direction;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
};

struct PointLight {
    
    Vec3 position;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {

    Vec3 position;
    Vec3 direction;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    
    float cutoff;
    float outer_cutoff;
};