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
    float exposure                  = 1.0f;

    int animation_stage             = -1;

    bool animate                    = false;
    float animation_time            = 0.0f;

    // 
    float vertex_divider            = 1.0f; // for drawing certain faces on a mesh

    // material
    float emission_factor           = 0.0f;
    float shininess                 = 0.0f;

    // predefined_scene_element_transforms
    std::vector<Transform> transforms;
    // techniques
    std::vector<ElementBools> model_element_bools;
    std::string model_shader_name = "multiplelights";

    // bools
    bool toggle_ui = false;
    bool display_axes = false;
    bool display_skybox = false;
    bool display_normals = false;
    bool display_shadows = true;

    bool toggle_ssao                = true;
    bool explode_model              = false;
    bool use_computed_data          = false;
    bool use_bloom                  = true;
    bool use_deferred_shading       = false;
    bool use_gamma_correction       = false;
    bool use_ssao                   = false;

    unsigned int instance_count = 100;
    bool draw_instanced = false;

    // stats
    unsigned int stats_vrts = 0;
    unsigned int stats_tris = 0;



    // testing
    bool        b_model_refraction = false;

};