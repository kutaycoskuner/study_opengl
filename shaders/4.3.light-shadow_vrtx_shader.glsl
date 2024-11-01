#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texcoords;

out VS_OUT {
    vec3 v_world_pos;
    vec3 v_normal;
    vec2 v_texcoords;
    vec4 v_lightspace_pos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{    
    vs_out.v_world_pos = vec3(model * vec4(in_pos, 1.0));
    vs_out.v_normal = transpose(inverse(mat3(model))) * in_normal;
    vs_out.v_texcoords = in_texcoords;
    vs_out.v_lightspace_pos = lightSpaceMatrix * vec4(vs_out.v_world_pos, 1.0);
    gl_Position = projection * view * vec4(vs_out.v_world_pos, 1.0);
}