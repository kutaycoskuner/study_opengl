#version 330 core
#if 1
// abstract
// ---------------------------------------------------------------------------------------
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

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outer_cutoff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
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

// globals = uniform variables
// ---------------------------------------------------------------------------------------
#define NR_POINT_LIGHTS 3
out vec4 f_frag_color;

in vec3 v_normal;  
in vec3 v_world_pos;
in vec2 v_tex_coords;

uniform vec3 view_pos;
uniform Material material;
uniform Light light;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;

// function declarations
// ---------------------------------------------------------------------------------------
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir);  
vec3 calcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

// main
// ---------------------------------------------------------------------------------------
void main()
{
    // define output color value
    vec3 illumination = vec3(0.0f);

    // calculate properties
    vec3 normal = normalize(v_normal);
    vec3 view_dir = normalize(view_pos - v_world_pos);
    vec3 emission_texture = vec3(texture(material.emission_map, v_tex_coords));

    // add directional light
    illumination += calcDirectionalLight(directional_light, normal, view_dir) / 2.0f;

    // add point light
     for(int ii = 0; ii < NR_POINT_LIGHTS; ii++)
     {
        illumination += calcPointLight(point_lights[ii], normal, v_world_pos, view_dir);    
     }

    // add spot light
    illumination += calcSpotLight(spot_light, normal, v_world_pos, view_dir);
//    illumination += emission_texture;
    
    // result
    f_frag_color = vec4(illumination, 1.0f);
}

// function definitons
// ---------------------------------------------------------------------------------------
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular_map, v_tex_coords));
    return (ambient + diffuse + specular);
}  

vec3 calcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - frag_pos);
    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular_map, v_tex_coords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - frag_pos);
    // diffuse shading
    float diff = max(dot(normal, light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(light_dir, normalize(-light.direction)); 
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_map, v_tex_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular_map, v_tex_coords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

#endif