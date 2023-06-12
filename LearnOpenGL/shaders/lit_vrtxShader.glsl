#version 330 core
#if 1
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal; 
out vec3 world_pos;

uniform mat4 world_matrix;
uniform mat4 view_proj_matrix;

void main()
{
	mat3 world_normal_matrix = mat3(transpose(inverse(world_matrix)));
	normal = vec3(world_normal_matrix * aNormal);
	world_pos = vec3(world_matrix * vec4(aPos, 1.0f));
	gl_Position = view_proj_matrix * world_matrix * vec4(aPos, 1.0f);
}
#endif