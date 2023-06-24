#pragma once

#include "../abstract/vector3.h"
#include "../abstract/camera.h"
#include "../abstract/light.h"
#include <vector>

struct SceneState
{
    // camera 
    Camera camera;
    // todo: move in to camera
    float aspect_ratio;
    float near;
    float far;
    float fov;

    // light
    Light light;

    // animation
    float time;
    float delta_time;
    float last_frame_time;
    float angle_multiplier;
    bool b_animate;
    float animation_time;

    // positions
    std::vector<Vec3> obj_positions;
    std::vector<Vec3> obj_colors;

    // ui
    bool b_toggleui;
};