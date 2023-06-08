#pragma once

#include "../abstract/vector3.h"
#include "../abstract/Camera.h"
#include <vector>

struct SceneState
{
    // frustum
    // todo: move in to camera
    float aspect_ratio;
    float near;
    float far;
    float fov;

    // camera
    Camera camera;

    // light
    Vec3 light_color;

    // animation
    float delta_time;
    float last_frame_time;
    float time;
    bool b_animate;

    // positions
    std::vector<Vec3> obj_positions;
    std::vector<Vec3> obj_colors;
};