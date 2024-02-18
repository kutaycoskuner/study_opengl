
#version 330 core
out vec4 f_fragcolor;

in vec3 v_tex_coords;

uniform samplerCube skybox;

void main()
{    
    f_fragcolor = texture(skybox, v_tex_coords);
}