#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coord;

out vec2 v_tex_coord;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * world_matrix * vec4(in_pos, 1.0);
    v_tex_coord = in_tex_coord;
}
#endif