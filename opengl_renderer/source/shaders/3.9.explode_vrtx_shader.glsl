#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec2 in_tex_coords;

out VS_OUT {
    vec2 tex_coords;
} vs_out;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 world_mat;

void main()
{
    vs_out.tex_coords = in_tex_coords;
    gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0); 
}