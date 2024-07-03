#version 330 core
layout (location = 0) in vec3 in_pos;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 world_matrix;

void main()
{
    gl_Position = projection * view * world_matrix * vec4(in_pos, 1.0);
}  