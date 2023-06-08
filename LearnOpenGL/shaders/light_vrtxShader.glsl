#version 330 core
#if 1
layout (location = 0) in vec3 aPos;

uniform mat4 world_matrix;
uniform mat4 view_proj_matrix;

void main()
{
	
	gl_Position = view_proj_matrix * world_matrix * vec4(aPos, 1.0f);
}
#endif