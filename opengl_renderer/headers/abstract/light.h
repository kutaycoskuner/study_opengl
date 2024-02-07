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
struct DirectionalLight {
    
    Vec3 direction;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;

    float brightness;
};

struct PointLight {
    
    Vec3 position;

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float brightness;
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

    float brightness;
};


//struct Lights {
//    std::vector<DirectionalLight> directional_lights;
//    std::vector<PointLight> point_lights;
//    std::vector<SpotLight> spot_lights;
//};

// ----- old
// ----------------------------------------------------------------------------

//struct Light
//{
//    Vec3 direction;
//	Vec3 position;
//
//    Vec3 color;
//    float brightness;
//
//	Vec3 ambient;
//	Vec3 diffuse;
//	Vec3 specular;
//
//    float constant;
//    float linear;
//    float quadratic;
//
//    float inner_cutoff;
//    float outer_cutoff;
//};