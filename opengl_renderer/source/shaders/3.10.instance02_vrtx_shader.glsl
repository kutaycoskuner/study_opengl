#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec2 in_tex_coords;
//layout (location = 3) in mat4 in_instance_mat;

out vec2 v_tex_coords;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 world_mat;

//uniform mat4 transformation_mat[1000];

struct instance_data {
    mat4 transformation_mat[1000];
};

uniform instance_data ins_data_uniform;


void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0); 

//    gl_Position = projection_mat * view_mat * ins_data_uniform.transformation_mat[gl_InstanceID] * vec4(in_pos, 1.0); 
    v_tex_coords = in_tex_coords;
}