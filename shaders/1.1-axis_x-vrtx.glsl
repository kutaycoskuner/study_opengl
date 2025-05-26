#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_norm;
layout (location = 2) in vec2 in_tex_coords;

out vec3 v_world_pos;

uniform mat4 world_matrix;
uniform mat4 view_proj_matrix;

void main()
{
	gl_Position = view_proj_matrix * world_matrix * vec4(in_pos, 1.0f);
	mat3 world_normal_matrix = mat3(transpose(inverse(world_matrix)));
	v_world_pos = vec3(world_matrix * vec4(in_pos, 1.0f));
}
#endif