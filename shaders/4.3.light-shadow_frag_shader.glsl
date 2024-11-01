#version 330 core
out vec4 f_frag_color;

in VS_OUT {
    vec3 v_world_pos;
    vec3 v_normal;
    vec2 v_texcoords;
    vec4 v_lightspace_pos;
} fs_in;

uniform sampler2D color_texture;
uniform sampler2D shadow_map;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // [...]
}

void main()
{           
    vec3 color = texture(color_texture, fs_in.v_texcoords).rgb;
    vec3 normal = normalize(fs_in.v_normal);
    vec3 lightColor = vec3(1.0);

    // ambient
    vec3 ambient = 0.15 * lightColor;
    
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.v_world_pos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.v_world_pos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.v_lightspace_pos);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    f_frag_color = vec4(lighting, 1.0);
}