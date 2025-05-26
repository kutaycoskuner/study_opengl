#version 330 core

out vec4 f_color;
in vec2 v_tex_coords;

void main()
{
    f_color = vec4(v_tex_coords, 1.0f, 1.0);
}