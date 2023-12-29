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
    float emission_factor;

    Vec3  obj_position;
    float obj_rotation_angle_y;
    Vec3  obj_scale;

    // positions
    std::vector<Vec3> obj_positions;
    std::vector<Vec3> obj_colors;

    // models
    std::vector<Model> models;

    // ui
    bool b_toggleui;
};