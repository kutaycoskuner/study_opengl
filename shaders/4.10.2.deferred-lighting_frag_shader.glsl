#version 330 core
out vec4 f_frag_color;
  
in vec2 v_tex_coords;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color_specular;

struct Light {
    vec3 position;
    vec3 color;
};

const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 view_pos;

void main()
{             
    // retrieve data from G-buffer
    vec3 frag_pos = texture(g_position, v_tex_coords).rgb;
    vec3 normal = texture(g_normal, v_tex_coords).rgb;
    vec3 color = texture(g_color_specular, v_tex_coords).rgb;
    float specular = texture(g_color_specular, v_tex_coords).a;
    
    // then calculate lighting as usual
    vec3 lighting = color * 0.01; // hard-coded ambient component
    vec3 view_dir = normalize(view_pos - frag_pos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // diffuse
        vec3 light_dir = normalize(lights[i].position - frag_pos);
        vec3 diffuse = max(dot(normal, light_dir), 0.0) * color * lights[i].color * 0.1;
        lighting += diffuse;
    }
    
    f_frag_color = vec4(lighting, 1.0);
}  