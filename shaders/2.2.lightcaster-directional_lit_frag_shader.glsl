#version 330 core
#if 1
struct Light
{
    vec3 direction;
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    vec3 diffuse;
	sampler2D diffuse_map;
    sampler2D specular_map;
    sampler2D emission_map;
	vec3 specular;
    float emission_factor;
	float shininess;
};

out vec4 f_frag_color;

in vec3 v_normal;  
in vec3 v_world_pos;
in vec2 v_tex_coords;

uniform vec3 view_pos;
uniform Material material;
uniform Light light;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;


void main()
{
    
    // texture
    vec3 diffuse_texture = vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 specular_texture = vec3(texture(material.specular_map, v_tex_coords));
    vec3 emission_texture = vec3(texture(material.emission_map, v_tex_coords));

    // light dir constant
    // ----------------------------------------------------------------------------------
    vec3 fragto_light_dir = normalize(-light.direction);

    // ambient calculation
    // ----------------------------------------------------------------------------------
    vec3 ambient_illumination = light.ambient
        * diffuse_texture
    ;

    // diffuse light calculation
    // ----------------------------------------------------------------------------------
    vec3 out_normal = normalize(v_normal);
    float diffuse_factor = max(dot(out_normal, fragto_light_dir) ,0.0f);
    vec3 diffuse_illumination = light.diffuse 
        * diffuse_factor
        * diffuse_texture
    ;

    // specular calculation
    // ----------------------------------------------------------------------------------
    float shininess = material.shininess; 
    vec3 view_dir = normalize(view_pos - v_world_pos);
    vec3 reflection_dir = reflect(-fragto_light_dir, out_normal);
    float specular_factor = pow(max(dot(view_dir, reflection_dir), 0.0), shininess);
    vec3 specular_illumination =  light.specular 
        * specular_factor 
        * specular_texture

    ;   

    // emission calculation
    // ----------------------------------------------------------------------------------
    float emission_mask = length(specular_texture) < .1f ? 1.0f : 0.0f;
    vec3 emission_illumination = abs(material.emission_factor 
        * emission_texture
        * emission_mask
        * 0.0f
        )
    ;

    // result
    // ----------------------------------------------------------------------------------
    vec4 calc_obj_color1 = texture(texture1, v_tex_coords);
    vec3 illumination = ambient_illumination 
        + diffuse_illumination 
        + specular_illumination
        + emission_illumination
    ;
    f_frag_color = vec4(illumination, 1.0f);
}
#endif