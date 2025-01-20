#version 330 core
#if 1
// notes
// ---------------------------------------------------------------------------------------
/*
    Shader name: hdr 

*/

// ---------------------------------------------------------------------------------------
//              abstract
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
    sampler2D depth_map1;
    sampler2D normal_map1;
    sampler2D emission_map1;
    float emission_factor;
    float shininess;
};

struct Surface {
    vec3 normal;
    vec3 normal_tangent_space;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
};

// ---------------------------------------------------------------------------------------
//              globals = uniform variables
// ---------------------------------------------------------------------------------------
#define NR_POINT_LIGHTS 4
out vec4 f_frag_color;

in VS_OUT {
    vec3 world_position;
    vec3 world_normal;
    vec2 tex_coords;
    mat3 tbn;
} fs_in;

uniform vec3 view_pos;
uniform float far_plane;
uniform Material material;

uniform int num_point_lights;
uniform DirectionalLight directional_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;

// New shadow-related uniforms
uniform sampler2D shadow_map;      // Shadow map for the light
uniform samplerCube shadow_cubemap;

// parallax related
uniform float prlx_height_scale;

// array of offset direction for sampling
vec3 grid_sampling_disk[20] = vec3[](vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1), vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1));

// ---------------------------------------------------------------------------------------
//              function definitions
// ---------------------------------------------------------------------------------------

// Shadow calculation function
float ShadowCalculation(vec3 world_pos) {
    world_pos.z = -world_pos.z;
     // get vector between fragment position and light position
    vec3 frag_distance_to_light = world_pos - point_lights[0].position; 
     // now get current linear depth as the length between the fragment and light position
    float current_depth = length(frag_distance_to_light);

     // now test for shadows
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float view_distance = length(view_pos - world_pos);
    float disk_radius = (1.0 + (view_distance / far_plane)) / 25.0;

    for(int i = 0; i < samples; ++i) {
        float closest_depth = texture(shadow_cubemap, frag_distance_to_light + grid_sampling_disk[i] * disk_radius).r;
        closest_depth *= far_plane;   // undo mapping [0;1]
        if(current_depth - bias > closest_depth)
            shadow += 0.6;
    }
    shadow /= float(samples);

    return shadow;
}  

//float ShadowCalculation(vec3 world_pos)
//{
//    // get vector between fragment position and light position
////    world_pos.y = -world_pos.y;
////    world_pos.x = -world_pos.x;
//    world_pos.z = -world_pos.z;
//    vec3 frag_distance_to_light = world_pos - point_lights[0].position;
//    // use the light to fragment vector to sample from the depth map    
////    shadow_cubemap.z = -shadow_cubemap.z;
////    shadow_cubemap.y = -shadow_cubemap.y;
//    float closest_depth = texture(shadow_cubemap, frag_distance_to_light).r;
//    // it is currently in linear range between [0,1]. Re-transform back to original value
//    closest_depth *= far_plane;
//    // now get current linear depth as the length between the fragment and light position
//    float current_depth = length(frag_distance_to_light);
//    // now test for shadows
//    float bias = 0.05; 
//    float shadow = current_depth -  bias > closest_depth ? 1.0 : 0.0;
//
//    return shadow;
//} 

//float ShadowCalculation(vec4 light_space_position, float shadow_bias) {
//    // perform perspective divide
//    vec3 proj_coords = light_space_position.xyz / light_space_position.w;
//
//    // normalize to 0-1 range as kn depth map
//    proj_coords = proj_coords * 0.5 + 0.5;
//
//    // sample from shadow map to closest depth
//    float closest_depth_sample = texture(shadow_map, proj_coords.xy).r;
//
//    // current depth
//    float current_depth = proj_coords.z;
//
////    float bias = 0.005f;
////     shadow_bias = 0.005f;
//    // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
//    // compare depths for machine to comprehend shadow
//    float shadow = current_depth - shadow_bias > closest_depth_sample ? 0.6 : 0.0;
//
//    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
//    for(int x = -1; x <= 1; ++x) {
//        for(int y = -1; y <= 1; ++y) {
//            float pcf_depth = texture(shadow_map, proj_coords.xy + vec2(x, y) * texel_size).r;
//            shadow += current_depth - shadow_bias > pcf_depth ? 1.0 : 0.0;
//        }
//    }
//    shadow /= 9.0;
//
//    if(proj_coords.z > 1.0)
//        shadow = 0.0;
//
//    shadow = 0.0f;
//    return shadow;
//}

// Modify the lighting functions to incorporate shadows
vec3 calcDirectionalLight(DirectionalLight light, Surface surface, vec3 view_dir) {
    vec3 light_dir = normalize(fs_in.tbn * -light.direction);
	

    float diff = max(dot(surface.normal, light_dir), 0.0);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(view_dir, halfway_dir), 0.0), 32.0);

    vec3 ambient = light.ambient * surface.diffuse;
    vec3 diffuse = light.diffuse * diff * surface.diffuse;
    vec3 specular = light.specular * spec * surface.specular;

    // Apply shadow calculation
    //    float shadow_bias = max(0.005 * (1.0 - dot(normalize(surface.normal), -light_dir)), 0.0005);
    //    float shadow = ShadowCalculation(fs_in.light_space_position, shadow_bias);
    float shadow = 0.0;
    // Combine results and apply brightness, factoring in shadow
    //return vec3(spec);
	//return light_dir;
	//return ;
    return (ambient + (1.0) * (diffuse + specular)) * light.brightness;
}

vec3 calcPointLight(PointLight p_light, Surface p_surface, vec3 p_frag_pos, vec3 p_view_dir) {

	// yuzeyden isiga giden vektor
    vec3 light_dir = normalize(p_light.position - p_frag_pos);

    // vec3 tan_pos      = fs_in.tbn * fs_in.world_position;
    // vec3 tan_view_pos = fs_in.tbn * view_pos;
    // vec3 tan_view_dir = normalize(tan_view_pos - tan_pos);
    // diffuse shading
    float diff = max(dot(p_surface.normal, light_dir), 0.0);

    // specular shading
    //vec3 reflect_dir = reflect(-light_dir, surface.normal);
    vec3 halfway_dir = normalize(light_dir + p_view_dir);
    float spec = pow(max(dot(p_surface.normal, halfway_dir), 0.0), material.shininess);

    // attenuation
    float distance = length(p_light.position - p_frag_pos);
    float attenuation = 1.0 / (p_light.constant + p_light.linear * distance + p_light.quadratic * (distance * distance));

    // combine results
    vec3 ambient    = p_light.ambient * p_surface.diffuse;
    vec3 diffuse    = p_light.diffuse * diff * p_surface.diffuse;
    vec3 specular   = p_light.specular * spec * p_surface.specular;
    ambient         *= attenuation;
    diffuse         *= attenuation;
    specular        *= attenuation;

	// return halfway_dir;
    float shadow = ShadowCalculation(fs_in.world_position);
    shadow = 0.0f;
    // return surface.normal * 1.0f;
//    return (p_light.position);
    return (ambient + (1.0 - 0.0) * (diffuse + specular)) * p_light.brightness;
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

vec2 parallaxMapping(vec2 tex_coords, vec3 view_dir) {
    float height = texture(material.depth_map1, tex_coords).r;    
//    height_vec = normalize(height * 2.0 - 1.0); 
//    height_vec = fs_in.tbn * height_vec;
//    float height = height_vec.r;
//    vec2 p = view_dir.xy / view_dir.z * (height * prlx_height_scale);
    // displacementi bakis acisina gore scale ediyor. view dir normalize oldugu icin z 0, 1 arasinda bir yerde
    vec2 p = view_dir.xy / view_dir.z * (height * prlx_height_scale);
    return tex_coords - p;
}

vec2 SteepParallaxMapping(vec2 texCoords, vec3 viewDir) { 
    // number of depth layers
    const float numLayers = 10;
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = vec2(viewDir.x, -viewDir.y) * prlx_height_scale;
    vec2 deltaTexCoords = P / numLayers;

    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(material.depth_map1, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(material.depth_map1, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    return currentTexCoords;
}

vec2 ParallaxOcclusionMapping(vec2 p_tex_coords, vec3 p_view_dir) { 
    // number of depth layers
	//p_tex_coords = vec2(p_tex_coords.x, p_tex_coords.y);
    const float num_layers = 10;
    // calculate the size of each layer
    float layer_depth = 1.0 / num_layers;
    // depth of current layer
    float curr_layer_depth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 p = vec2(p_view_dir.x, p_view_dir.y) * prlx_height_scale;
    vec2 delta_tex_coords = p / num_layers;

    vec2 curr_tex_coords = p_tex_coords;
    float curr_depthmap_val = texture(material.depth_map1, curr_tex_coords).r;

    while(curr_layer_depth < curr_depthmap_val) {
        // shift texture coordinates along direction of P
        curr_tex_coords -= delta_tex_coords;
        // get depthmap value at current texture coordinates
        curr_depthmap_val = texture(material.depth_map1, curr_tex_coords).r;  
        // get depth of next layer
        curr_layer_depth += layer_depth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prev_tex_coords = curr_tex_coords + delta_tex_coords;

    // get depth after and before collision for linear interpolation
    float after_depth = curr_depthmap_val - curr_layer_depth;
    float before_depth = texture(material.depth_map1, prev_tex_coords).r - curr_layer_depth + layer_depth;

    // interpolation of texture coordinates
    float weight = after_depth / (after_depth - before_depth);
    vec2 final_tex_coords = prev_tex_coords * weight + curr_tex_coords * (1.0 - weight);

//    return p_tex_coords;
    return final_tex_coords;
} 

vec3 srgb_to_linear(vec3 srgb_color) 
{
    return pow(srgb_color, vec3(2.2));
}


// ---------------------------------------------------------------------------------------
//              main
// ---------------------------------------------------------------------------------------
void main() {

    // compute
    // -----------------------------------------------------------------------------------
//    vec3 view_dir   = normalize(view_pos - fs_in.world_position);

    vec3 tan_space_world_pos = fs_in.tbn * fs_in.world_position;
    vec3 tan_space_view_pos  = fs_in.tbn * view_pos;
    vec3 tan_space_view_dir  = normalize(tan_space_view_pos - tan_space_world_pos);

    vec2 tex_coords = vec2(fs_in.tex_coords);
//    tex_coords = parallaxMapping(fs_in.tex_coords, tan_space_view_dir);
    // vec2 tex_coords = SteepParallaxMapping(fs_in.tex_coords, tan_space_view_dir);
//    tex_coords = ParallaxOcclusionMapping(fs_in.tex_coords, tan_space_view_dir);

 
//    if(tex_coords.x > 1.0 || tex_coords.y > 1.0 || tex_coords.x < 0.0 || tex_coords.y < 0.0)
//        discard;
//    vec2 tex_coords = fs_in.tex_coords;

    vec3 illumination = vec3(0.0);
    Surface surface;

    // set textures
    // -----------------------------------------------------------------------------------
    // set normal
    //    surface.normal = normalize(fs_in.normal);
    surface.normal = texture(material.normal_map1, vec2(tex_coords.x, tex_coords.y)).rgb;
    surface.normal = normalize(surface.normal * 2.0 - 1.0); 
//    surface.normal = fs_in.tbn * surface.normal;

    //    if (surface.specular == vec3(0.0)) {surface.specular = vec3(0.0f, 0.0f, 1.0f);}

    // diffuse
    vec4 diffuse_map_sample = texture(material.diffuse_map1, tex_coords);
     diffuse_map_sample.rgb = srgb_to_linear(diffuse_map_sample.rgb);

    // alpha masking
    if(diffuse_map_sample.a < 0.02)
        discard;

    surface.diffuse = diffuse_map_sample.rgb;
    surface.diffuse = srgb_to_linear(diffuse_map_sample.rgb);

    // set specular
    surface.specular = vec3(texture(material.specular_map1, tex_coords));
    if(surface.specular == vec3(0.0)) {
        //surface.specular = vec3(0.4, 0.4, 0.4);
    }

    // set emission
    surface.emission = vec3(texture(material.emission_map1, tex_coords));
    // todo bunun da gammaya cekilmsei lazim
    //    if (surface.emission == vec3(0.0)) { surface.emission = vec3(1.0f, 1.0f, 1.0f); }

    // illuminate
    // -----------------------------------------------------------------------------------
    // Add directional light with shadows
    illumination += calcDirectionalLight(directional_light, surface, tan_space_view_dir);

    // Add point lights with shadows
    for(int ii = 0; ii < num_point_lights; ii++) {
        PointLight tan_space_light = point_lights[ii];
        tan_space_light.position = fs_in.tbn * tan_space_light.position;
        illumination += calcPointLight(tan_space_light, surface, tan_space_world_pos, tan_space_view_dir);
//        illumination += calcPointLight(point_lights[ii], surface, fs_in.world_position, view_dir);
    }

    // Add spotlight with shadows
    //    illumination += calcSpotLight(spot_light, surface, fs_in.world_position, view_dir);

    // Add emission
    if(material.emission_factor > 0) {
        //illumination += surface.emission * material.emission_factor;
    }

    // result
    // -----------------------------------------------------------------------------------
    // Set final color output
    f_frag_color = vec4(illumination, 1.0);

    // debug
    // -----------------------------------------------------------------------------------
//    f_frag_color = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0);
     //surface.normal = fs_in.world_normal;
	 //f_frag_color = vec4(surface.normal, 1.0);
//     
//    f_frag_color = vec4(tan_space_view_dir * 0.5 + 0.5, 1.0);
//    float f = texture(material.depth_map1, tex_coords).r;
    //f_frag_color = vec4(vec3(tex_coords, 0.0f), 1.0);
//    f_frag_color = vec4(fs_in.tbn[2], 1.0f);

}

#endif