#version 330 core
layout (location = 0) in vec3 in_pos;

out VS_OUT {
    vec3 normal;
} vs_out[];

uniform mat4 world_mat;

void main()
{

    gl_Position =  world_mat * vec4(in_pos.x, in_pos.y, in_pos.z, 1.0f);


}
