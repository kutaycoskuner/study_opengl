#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;

out vec3 v_frag_pos;
out vec2 v_tex_coords;
out vec3 v_normal;

uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;



void main()
{
    vec4 world_pos = view_mat * world_mat * vec4(in_pos, 1.0);
    v_frag_pos = world_pos.xyz; 
    v_tex_coords = in_tex_coords;
    
    mat3 normal_mat = transpose(inverse(mat3(world_mat)));
    v_normal = normal_mat * in_normal;

    gl_Position = projection_mat * world_pos;
}