#version 330 core
#if 1
struct Light
{
    vec3 direction;
	vec3 position;

    vec3 color;
    float brightness;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float inner_cutoff;
    float outer_cutoff;
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
    // ----------------------------------------------------------------------------------
    vec3 diffuse_texture = vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 specular_texture = vec3(texture(material.specular_map, v_tex_coords));
    vec3 emission_texture = vec3(texture(material.emission_map, v_tex_coords));

    // attenuation calculation
    // ----------------------------------------------------------------------------------
    float distance = length(light.position - v_world_pos);
    float distance_sq = distance * distance;
    vec3 fragto_light_dir = normalize(light.position - v_world_pos);
    //    vec3 fragto_light_dir = normalize(-light.direction);
    float attenuation 
        = 1.0f / (
        light.constant 
        + light.linear * distance
        + light.quadratic * distance_sq
        )
    ;

    // ambient calculation
    // ----------------------------------------------------------------------------------
    vec3 ambient_illumination = light.ambient
        * diffuse_texture
        * attenuation
    ;

    // spotlight check
    // ----------------------------------------------------------------------------------
    // angle between light direction and spot direction
    float cos_spot_angle = dot(fragto_light_dir, normalize(-light.direction));
    if (cos_spot_angle < light.outer_cutoff)
    {
        vec3 illumination = ambient_illumination;
        f_frag_color = vec4(illumination, 1.0f);
        return;
    }
    float epsilon = light.inner_cutoff - light.outer_cutoff;
    float intensity = clamp(
        (cos_spot_angle - light.outer_cutoff) / epsilon    
        , 0.0f
        , 1.0f
        ) 
        * light.brightness
    ;

    // diffuse light calculation
    // ----------------------------------------------------------------------------------
    vec3 out_normal = normalize(v_normal);
    float diffuse_factor = max(dot(out_normal, fragto_light_dir) ,0.0f);
    vec3 diffuse_illumination = light.diffuse 
        * diffuse_factor
        * diffuse_texture
        * attenuation
        * intensity
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
        * attenuation
        * intensity
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
    vec3 illumination = 
          ambient_illumination 
        + diffuse_illumination 
        + specular_illumination
        + emission_illumination
    ;
    f_frag_color = vec4(illumination, 1.0f);
}
#endif