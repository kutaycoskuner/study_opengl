#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coord;

out vec2 v_tex_coord;

uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0);
    v_tex_coord = in_tex_coord;
}
#endif