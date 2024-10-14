#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;


uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0);
}
#endif