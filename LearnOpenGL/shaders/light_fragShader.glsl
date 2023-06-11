#version 330 core
#if 1
out vec4 fragColor;

in vec3 normal;  
in vec3 world_pos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 


void main()
{
    // ambient calculation
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    // diffuse light params
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(lightPos - world_pos);
    float diffuse_factor = max(dot(normal, light_dir) ,0.0f);
    vec3 diffuse = diffuse_factor * lightColor;
    // 
    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0f);
//	fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	fragColor = vec4(objectColor * lightColor, 1.0f);
}
#endif