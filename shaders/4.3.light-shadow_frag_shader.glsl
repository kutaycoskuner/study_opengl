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

in VS_OUT {
    vec3 world_position;
    vec3 normal;
    vec2 tex_coords;
    vec4 light_space_position;
} fs_in;

uniform vec3 view_pos;
uniform Material material;

uniform int num_point_lights;
uniform DirectionalLight directional_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;

// New shadow-related uniforms
uniform sampler2D shadow_map;      // Shadow map for the light

// function definitions
// ---------------------------------------------------------------------------------------

// Shadow calculation function
float ShadowCalculation(vec4 light_space_position, float shadow_bias) {
    // perform perspective divide
    vec3 proj_coords = light_space_position.xyz / light_space_position.w;

    // normalize to 0-1 range as kn depth map
    proj_coords = proj_coords * 0.5 + 0.5; 

    // sample from shadow map to closest depth
    float closest_depth_sample = texture(shadow_map, proj_coords.xy).r;

    // current depth
    float current_depth = proj_coords.z;

//    float bias = 0.005f;
//     shadow_bias = 0.005f;
    // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // compare depths for machine to comprehend shadow
    float shadow = current_depth - shadow_bias > closest_depth_sample ? 0.6 : 0.0;

    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcf_depth = texture(shadow_map, proj_coords.xy + vec2(x, y) * texel_size).r;
            shadow += current_depth - shadow_bias > pcf_depth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(proj_coords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

// Modify the lighting functions to incorporate shadows
vec3 calcDirectionalLight(DirectionalLight light, Surface surface, vec3 view_dir) {
    vec3 light_dir = normalize(light.direction);
    float diff = max(dot(surface.normal, -light_dir), 0.0);
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 ambient = light.ambient * surface.diffuse;
    vec3 diffuse = light.diffuse * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;

    // Apply shadow calculation
    float shadow_bias = max(0.005 * (1.0 - dot(normalize(surface.normal), -light_dir)), 0.0005);
    float shadow = ShadowCalculation(fs_in.light_space_position, shadow_bias);

    // Combine results and apply brightness, factoring in shadow
    return (ambient + (1.0 - shadow) * (diffuse + specular)) * light.brightness;
}

vec3 calcPointLight(PointLight light, Surface surface, vec3 frag_pos, vec3 view_dir) {
    vec3 light_dir = normalize(frag_pos - light.position);
    // diffuse shading
    float diff = max(dot(surface.normal, -light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * surface.diffuse;
    vec3 diffuse = light.diffuse * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.brightness;
}

vec3 calcSpotLight(SpotLight light, Surface surface, vec3 frag_pos, vec3 view_dir) {
    vec3 light_dir = normalize(frag_pos - light.position);
    // diffuse shading
    float diff = max(dot(surface.normal, -light_dir), 0.0);
    // specular shading
    vec3 reflect_dir = reflect(light_dir, surface.normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(light_dir, normalize(light.direction));
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * surface.diffuse;
    vec3 diffuse = light.diffuse * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.brightness;
}

// main
// ---------------------------------------------------------------------------------------
void main() {
    vec3 illumination = vec3(0.0);

    Surface surface;
    surface.normal = normalize(fs_in.normal);
    surface.diffuse = vec3(texture(material.diffuse_map1, fs_in.tex_coords));
    surface.specular = vec3(texture(material.specular_map1, fs_in.tex_coords));
    surface.emission = vec3(texture(material.emission_map1, fs_in.tex_coords));

    vec3 view_dir = normalize(view_pos - fs_in.world_position);

    // Add directional light with shadows
    illumination += calcDirectionalLight(directional_light, surface, view_dir);

    // Add point lights with shadows
    for(int ii = 0; ii < num_point_lights; ii++) {
//        illumination += calcPointLight(point_lights[ii], surface, fs_in.world_position, view_dir);
    }

    // Add spotlight with shadows
//    illumination += calcSpotLight(spot_light, surface, fs_in.world_position, view_dir);

    // Add emission
    if(material.emission_factor > 0) {
        illumination += surface.emission * material.emission_factor;
    }

    // Set final color output
    f_frag_color = vec4(illumination, 1.0);
}

#endif