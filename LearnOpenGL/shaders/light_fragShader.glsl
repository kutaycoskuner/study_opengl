#version 330 core
#if 1
out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;


void main()
{
//	fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	fragColor = vec4(objectColor * lightColor, 1.0f);
}
#endif