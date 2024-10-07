#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in mat4 in_instance_mat;

out vec2 v_tex_coords;


layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat4 transformation[1000];
};


uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 world_mat;
//uniform mat4 transformation_mat[1000];


void main()
{
//    gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0); 
//    gl_Position = projection * view * transformation[gl_InstanceID] * vec4(in_pos, 1.0); 

//    gl_Position = projection_mat * view_mat * transformation_mat[gl_InstanceID] * vec4(in_pos, 1.0); 

    // method 5
    gl_Position = projection_mat * view_mat * in_instance_mat * vec4(in_pos, 1.0); 

    v_tex_coords = in_tex_coords;
}