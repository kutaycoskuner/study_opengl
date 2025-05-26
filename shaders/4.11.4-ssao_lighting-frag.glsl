#version 330 core
/*
        Shader name: ssao-lighting pass
*/
out vec4 f_frag_color;

in vec2 v_tex_coords;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color_specular;
uniform sampler2D ssao;

uniform mat4 view_mat;

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

const int MAX_NR_POINT_LIGHTS = 32;
uniform int nr_point_lights;
uniform PointLight point_lights[MAX_NR_POINT_LIGHTS];
uniform bool is_ao_active;
// uniform vec3 view_pos;

void main()
{             
    // retrieve data from gbuffer
    vec3    frag_pos            = texture(g_position, v_tex_coords).rgb;
    vec3    normal              = texture(g_normal, v_tex_coords).rgb;
    vec3    diffuse_color       = texture(g_color_specular, v_tex_coords).rgb;
    float   ao                  = texture(ssao, v_tex_coords).r;
    
    // then calculate lighting as usual
    vec3 ambient                = vec3(diffuse_color * ao);
    if (!is_ao_active) ambient  = vec3(diffuse_color);
    ambient                     *= 0.3;
    vec3 lighting               = ambient; 
    vec3 view_dir               = normalize(- frag_pos); // viewpos is (0.0.0)
    
    // diffuse

    for(int i = 0; i < min(nr_point_lights, MAX_NR_POINT_LIGHTS); ++i)
    {
        // light dir calculation
        vec4 viewspace_light_pos4 = view_mat * vec4(point_lights[i].position, 1.0);
        vec3 viewspace_light_pos  = viewspace_light_pos4.xyz;
        vec3 light_dir            = normalize(viewspace_light_pos - frag_pos);
        vec3 diffuse_illumination = max(dot(normal, light_dir), 0.0) * diffuse_color * point_lights[i].diffuse;

        // specular
        vec3 halfway_dir            = normalize(light_dir + view_dir);  
        float spec_factor           = pow(max(dot(normal, halfway_dir), 0.0), 8.0);
        vec3 specular_illumination  = point_lights[i].diffuse * spec_factor;

        // attenuation
        float distance      = length(viewspace_light_pos - frag_pos);
        float attenuation   = 1.0 / (1.0 + point_lights[i].linear * distance + point_lights[i].quadratic * distance * distance);
        
        // attenuation update
        diffuse_illumination  *= attenuation;
        specular_illumination *= attenuation;
        lighting              += diffuse_illumination + specular_illumination;
    
    }
    
    f_frag_color = vec4(lighting, 1.0);
}