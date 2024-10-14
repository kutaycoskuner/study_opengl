#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 view_mat;
uniform mat4 world_mat;

void main()
{
    mat3 normal_mat = mat3(transpose(inverse(view_mat * world_mat)));
    vs_out.normal = vec3(vec4(normal_mat * in_normal, 0.0));
    gl_Position = view_mat * world_mat * vec4(in_pos, 1.0); 
}