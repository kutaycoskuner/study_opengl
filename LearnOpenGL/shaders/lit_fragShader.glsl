#version 330 core
#if 1
out vec4 fragColor;

in vec3 normal;  
in vec3 world_pos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 view_pos;


void main()
{
    // ambient calculation
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
    // diffuse light calculation
    vec3 out_normal = normalize(normal);
    vec3 light_dir = normalize(lightPos - world_pos);
    float diffuse_factor = max(dot(out_normal, light_dir) ,0.0f);
    vec3 diffuse = diffuse_factor * lightColor;
    // specular calculation
    float specular_strength = .5f;
    vec3 view_dir = normalize(view_pos - world_pos);
    vec3 reflection_dir = reflect(-light_dir, out_normal);
    float out_specular = pow(max(dot(view_dir, reflection_dir), 0.0), 32);
    vec3 specular = specular_strength * out_specular * lightColor;   
    // result
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0f);
//	fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	fragColor = vec4(objectColor * lightColor, 1.0f);
}
#endif