#version 330 core
#if 1
// abstract
// ---------------------------------------------------------------------------------------
struct DirectionalLight {
   
   vec3 direction;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
    float brightness;
};

struct PointLight {    
   
   vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    float brightness;
};  

struct SpotLight {
    
    vec3 position;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
  
    float constant;
    float linear;
    float quadratic;

    float cutoff;
    float outer_cutoff;
    float brightness;
};

struct Material {
    vec3 diffuse;
	vec3 specular;
    sampler2D diffuse_map1;
    sampler2D specular_map1;
    sampler2D emission_map1;
    float emission_factor;
	float shininess;
};

struct Surface {
    vec3 normal;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
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

uniform DirectionalLight directional_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;

// function definitons
// ---------------------------------------------------------------------------------------
vec3 calcDirectionalLight(DirectionalLight light, Surface surface, vec3 view_dir)
{
    // 
    vec3 light_dir = normalize(light.direction);
    // diffuse shading
    float diff = max(dot(surface.normal, -light_dir), 0.0f);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);

    // combine results
    vec3 ambient  = light.ambient  * surface.diffuse;
    vec3 diffuse  = light.diffuse  * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;
    return (ambient + specular + diffuse) * light.brightness;
}  

vec3 calcPointLight(PointLight light, Surface surface, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(frag_pos - light.position);
    // diffuse shading
    float diff = max(dot(surface.normal, -light_dir), 0.0f);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * surface.diffuse;
    vec3 diffuse  = light.diffuse  * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular)  * light.brightness;
}

vec3 calcSpotLight(SpotLight light, Surface surface, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(frag_pos - light.position);
    // diffuse shading
    float diff = max(dot(surface.normal, -light_dir), 0.0f);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(light_dir, normalize(light.direction)); 
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient  = light.ambient  * surface.diffuse;
    vec3 diffuse  = light.diffuse  * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.brightness;
}

// main
// ---------------------------------------------------------------------------------------
void main()
{
    // define output color value
    vec3 illumination = vec3(0.0f);
    vec3 dark = vec3(0.0f);


    // assign Surface
    Surface surface;
    surface.normal      = normalize(v_normal);
    surface.diffuse     = vec3(texture(material.diffuse_map1, v_tex_coords));
    surface.specular    = vec3(texture(material.specular_map1, v_tex_coords));
    surface.emission    = vec3(texture(material.emission_map1, v_tex_coords));
   

    // calculate properties
    vec3 view_dir = normalize(view_pos - v_world_pos);

    // add directional light
    illumination += calcDirectionalLight(directional_light, surface, view_dir);

     // add point light
     for(int ii = 0; ii < NR_POINT_LIGHTS; ii++)
     {
      illumination += calcPointLight(point_lights[ii], surface, v_world_pos, view_dir);    
     }

    // add spot light
    illumination += calcSpotLight(spot_light, surface, v_world_pos, view_dir);

    // add emission
    if (material.emission_factor > 0)
    {
        illumination += surface.emission * material.emission_factor;
    }

    // result
    //    f_frag_color = vec4(surface.diffuse, 1.0f);
    //    f_frag_color = vec4(dark, 1.0f);
    f_frag_color = vec4(illumination, 1.0f);
}

#endif