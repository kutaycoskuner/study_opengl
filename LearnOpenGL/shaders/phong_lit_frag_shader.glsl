#version 330 core
#if 1
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

out vec4 f_frag_color;

in vec3 v_normal;  
in vec3 v_world_pos;
in vec2 v_tex;

uniform vec3 view_pos;
uniform Material material;
uniform Light light;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;


void main()
{
    // ambient calculation
    vec3 ambient = light.ambient * material.ambient;

    // diffuse light calculation
    vec3 out_normal = normalize(v_normal);
    vec3 light_dir = normalize(light.position - v_world_pos);
    float diffuse_factor = max(dot(out_normal, light_dir) ,0.0f);
    vec3 diffuse = light.diffuse * (diffuse_factor * material.diffuse);

    // specular calculation
    float shininess = material.shininess; // source material datasi boyle kullaniyor. Gotumden carpmiyorum 128 ile
    vec3 view_dir = normalize(view_pos - v_world_pos);
    vec3 reflection_dir = reflect(-light_dir, out_normal);
    float out_specular = pow(max(dot(view_dir, reflection_dir), 0.0), shininess);
    vec3 specular =  light.specular * (out_specular * material.specular);   

    // result
    vec4 calc_obj_color1 = texture(texture1, v_tex);
    vec3 result = ambient + diffuse + specular;
    f_frag_color = vec4(result, 1.0f);
}
#endif