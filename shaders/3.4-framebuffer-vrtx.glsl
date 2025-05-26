#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex_coords;

out vec2 v_tex_coords;

void main()
{
    gl_Position = vec4(in_pos.x, in_pos.y, 0.0f, 1.0f);
    v_tex_coords = in_tex_coords;
}
#endif