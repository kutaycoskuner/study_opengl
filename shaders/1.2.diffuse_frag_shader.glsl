#version 330 core
#if 1
out vec4 out_frag_color;

in vec3 v_our_color;
in vec2 v_tex_coord;

uniform vec3 object_color;
uniform vec3 light_color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;


vec3 srgb_to_linear(vec3 srgb_color) 
{
    return pow(srgb_color, vec3(2.2));
}

vec3 linear_to_srgb(vec3 linear_color) 
{
    return pow(linear_color, vec3(1.0/2.2));
}

void main()
{
    out_frag_color = mix(texture(texture1, v_tex_coord), texture(texture2, v_tex_coord), mix_val);
    vec3 diffuse = texture(texture1, v_tex_coord).rgb;

    // gamma correction
//    diffuse = pow(diffuse, vec3(2.2));
    diffuse = srgb_to_linear(diffuse);

    out_frag_color = vec4(diffuse, 1.0);
}
#endif