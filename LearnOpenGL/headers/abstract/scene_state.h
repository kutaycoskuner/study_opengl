#pragma once

#include "../abstract/vector3.h"
#include <vector>

struct SceneState
{
    // frustum
    float aspect_ratio;
    float near;
    float far;

    // animate
    float time;
    bool b_animate;

    // positions
    std::vector<Vec3> obj_positions;
};