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
    float time;
    float delta_time;
    float last_frame_time;

    bool animate;
    float animation_time;

    // 
    float vertex_divider; // sadece belli yuzleri cizdirmek icin

    // material
    float emission_factor;
    float shininess;

    // predefined_scene_element_transforms
    std::vector<Transform> transforms;
    // techniques
    std::vector<ElementBools> model_element_bools;

    // ui
    bool b_toggleui;

    // testing
    bool        b_model_refraction = false;

};