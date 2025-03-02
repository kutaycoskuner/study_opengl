#version 330 core
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec4 g_color_specular;

in vec2 v_tex_coords;
in vec3 v_frag_pos;
in vec3 v_normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    g_position = v_frag_pos;
    // also store the per-fragment normals into the gbuffer
    g_normal = normalize(v_normal);
    // and the diffuse per-fragment color
    g_color_specular.rgb = texture(texture_diffuse1, v_tex_coords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    g_color_specular.a = texture(texture_specular1, v_tex_coords).r;
}  