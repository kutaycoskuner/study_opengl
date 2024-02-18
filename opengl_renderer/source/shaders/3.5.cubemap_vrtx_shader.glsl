#version 330 core
// ---------------------------------------------------------------------------------------
layout (location = 0) in vec3 in_pos;
layout (location = 0) in vec3 in_normal;


out vec3 v_tex_coords;

uniform mat4 view_proj_matrix;

void main()
{
    v_tex_coords = in_pos;
    vec4 pos = view_proj_matrix * vec4(in_pos, 1.0);
    /*
     The resulting normalized device coordinates will then always have a z value equal
     to 1.0: the maximum depth value. The skybox will as a result only be rendered 
     wherever there are no objects visible (only then it will pass the depth test, 
     everything else is in front of the skybox).
    */
    gl_Position = pos.xyww;
}  