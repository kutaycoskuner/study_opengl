#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex_coords;

out vec2 v_tex_coords;

void main()
{
    v_tex_coords = in_tex_coords;
    // burada view proj ile carpmiyoruz cunku g_pos zaten view da geliyor.  
    gl_Position = vec4(in_pos, 1.0);
}