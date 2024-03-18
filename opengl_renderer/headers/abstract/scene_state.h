#pragma once

#include "../abstract/vector3.h"
#include "../abstract/camera.h"
#include "../abstract/light.h"
#include "../abstract/model.h"
#include "../abstract/transform.h"
#include "../data/data.h"
#include <vector>


struct SceneState
{
    // primes
    Vec3 world_up;

    // animation
    float time                      = 0.0f;
    float time_pin                  = 0.0f;
    float time_difference           = 0.0f;
    float delta_time                = 0.0f;
    float last_frame_time           = 0.0f;

    float tant                      = 0.0f;

    unsigned int animation_stage    = -1;

    bool animate                    = false;
    float animation_time            = 0.0f;

    // 
    float vertex_divider            = 1.0f; // sadece belli yuzleri cizdirmek icin

    // material
    float emission_factor           = 0.0f;
    float shininess                 = 0.0f;

    // predefined_scene_element_transforms
    std::vector<Transform> transforms;
    // techniques
    std::vector<ElementBools> model_element_bools;
    std::string model_shader_name = "multiplelights";

    // ui
    bool b_toggleui = false;
    bool display_axes = false;
    bool display_skybox = false;
    bool display_normals = false;

    // bool
    bool model_explosion = false;


    // testing
    bool        b_model_refraction = false;

};