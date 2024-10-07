#version 330 core
#if 1
// globals = uniform variables
// ---------------------------------------------------------------------------------------
#define NR_POINT_LIGHTS 3
out vec4 f_frag_color;

in vec3 v_world_pos;

uniform vec3 view_pos;

// main
// ---------------------------------------------------------------------------------------
void main()
{
    f_frag_color = vec4(0.024f, 0.706f, 0.729f, 1.0f);
}

#endif