#version 330 core
#if 1
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;

out VS_OUT {
    vec3 world_position;
    vec3 normal;
    vec2 tex_coords;
} vs_out;

uniform mat4 world_mat;
uniform mat4 projection_mat;
uniform mat4 view_mat;

void main()
{    
    vs_out.world_position         = vec3(world_mat * vec4(in_position, 1.0));
    vs_out.normal                 = transpose(inverse(mat3(world_mat))) * in_normal;
    vs_out.tex_coords             = in_tex_coords;
//    vs_out.light_space_position   = light_space_matrix * vec4(vs_out.world_position, 1.0);
    
    gl_Position                     = projection_mat * view_mat * vec4(vs_out.world_position, 1.0);
}

#endif