#version 330 core
#if 1
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_norm;
layout (location = 2) in vec2 in_tex_coords;

out vec3 v_normal; 
out vec3 v_world_pos;
out vec2 v_tex_coords;

uniform mat4 world_matrix;
uniform mat4 view_proj_matrix;

uniform float outline_scale;
float base_outline_scale = 0.05f;

float near  = 1.0f;
float far   = 100.0f;


void main()
{
	// method 1.0: direct outline
	// vec3 currentPos = in_pos * (1.0f + base_outline_scale);
	
	// method 1.1: direct outline normalized thickness
	//	float test = pow(outline_scale, 0.6f);
	//	vec3 currentPos = in_pos * (1.0f + (base_outline_scale / test));
	
	// method 2.0: normal exposition
	//	vec3 currentPos = in_pos + (in_norm * base_outline_scale); 

	// method 2.1: normal exposition normalized thickness
	float scale_factor = pow(outline_scale, 0.6f);
	vec3 current_pos = in_pos + (in_norm * (base_outline_scale / scale_factor)); 
	gl_Position = view_proj_matrix * world_matrix * vec4(current_pos, 1.0f);
}
#endif

/*

scale: x: 100		y: 10	z: 1
after: x: 100.1   y. 10.1  z: 1.1

scale: x: 1		y: 1		z: 1
scale: x: 1.1     y: 1.1   z: 1.1

*/