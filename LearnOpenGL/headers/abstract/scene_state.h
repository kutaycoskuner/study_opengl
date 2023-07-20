#pragma once

#include "../abstract/vector3.h"
#include "../abstract/camera.h"
#include "../abstract/light.h"
#include "../abstract/model.h"
#include <vector>

struct SceneState
{
    // camera 
    Camera camera;

    // light
    std::vector<DirectionalLight> directional_lights;
    std::vector<PointLight> point_lights;
    std::vector<SpotLight> spot_lights;

    // animation
    float time;
    float delta_time;
    float last_frame_time;
    float angle_multiplier;
    bool animate;
    float animation_time;

    // positions
    std::vector<Vec3> obj_positions;
    std::vector<Vec3> obj_colors;

    // models
    Model model;

    // ui
    bool b_toggleui;
};