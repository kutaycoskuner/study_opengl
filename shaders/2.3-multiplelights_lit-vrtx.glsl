#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_norm;
layout (location = 2) in vec2 in_tex_coords;

out vec3		v_normal; 
out vec3		v_world_pos;
out vec2		v_tex_coords;

uniform mat4	world_mat;
uniform mat4	view_mat;
uniform mat4	projection_mat;
uniform mat4	view_proj_matrix;

uniform float	tiling_factor;

void main()
{
	gl_Position = projection_mat * view_mat * world_mat * vec4(in_pos, 1.0f);
	mat3 world_normal_matrix = mat3(transpose(inverse(world_mat)));
	v_world_pos = vec3(world_mat * vec4(in_pos, 1.0f));
	v_normal = vec3(world_normal_matrix * in_norm);
    v_tex_coords = in_tex_coords * tiling_factor;
}
#endif