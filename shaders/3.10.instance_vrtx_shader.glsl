//#version 330 core
//layout (location = 0) in vec2 in_pos;
//layout (location = 1) in vec3 in_color;
//
//out vec3 v_color;
//
//uniform vec2 offsets[100];
//
//void main()
//{
//    vec2 offset = offsets[gl_InstanceID];
//    gl_Position = vec4(in_pos + offset, 0.0, 1.0);
//    v_color = in_color;
//}  

#version 330 core
layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_offset;

out vec3 v_color;

void main()
{
    vec2 pos = in_pos * (gl_InstanceID / 100.0);
    gl_Position = vec4(pos + in_offset, 0.0, 1.0);
    v_color = in_color;
}  