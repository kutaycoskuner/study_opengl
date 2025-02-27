#version 330 core
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec4 g_color_specular;

in vec2 tex_coords;
in vec3 frag_pos;
in vec3 normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    g_position = frag_pos;
    g_position = vec3(1.0f, 0.0f, 0.0f);
    // also store the per-fragment normals into the gbuffer
    g_normal = normalize(normal);
    g_normal = vec3(0.0f, 1.0f, 0.0f);
    // and the diffuse per-fragment color
    g_color_specular.rgb = texture(texture_diffuse1, tex_coords).rgb;
    g_color_specular.rgb = vec3(0.0f, 0.0f, 1.0f);
    // store specular intensity in gAlbedoSpec's alpha component
    g_color_specular.a = texture(texture_specular1, tex_coords).r;
}  