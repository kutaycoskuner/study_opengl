#pragma once

#include "../abstract/vector3.h"
#include "../abstract/Camera.h"
#include <vector>

struct SceneState
{
    // frustum
    float aspect_ratio;
    float near;
    float far;
    float fov;

    // camera
    Camera camera;

    // animate
    float delta_time;
    float last_frame_time;
    float time;
    bool b_animate;

    // positions
    std::vector<Vec3> obj_positions;
};