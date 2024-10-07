#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;

out vec3 v_pos;
out vec3 v_normal;

uniform mat4 world_matrix;
uniform mat4 view_proj_matrix;

void main()
{
    v_normal = mat3(transpose(inverse(world_matrix))) * in_normal;
    v_pos = vec3(world_matrix * vec4(in_pos, 1.0));
    gl_Position = view_proj_matrix * vec4(v_pos, 1.0);
}  