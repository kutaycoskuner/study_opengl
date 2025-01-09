#version 330 core
#if 1
// notes
// ---------------------------------------------------------------------------------------
/*
    Shader name: 3d 

*/
out vec4 out_frag_color;

in vec3 v_our_color;
in vec2 v_tex_coord;

uniform vec3 object_color;
uniform vec3 light_color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;
uniform float light_brightness;


void main()
{
    vec4 tex_color = texture(texture1, v_tex_coord);
    out_frag_color = mix(texture(texture1, v_tex_coord), texture(texture2, v_tex_coord), mix_val);
    out_frag_color = vec4(light_color * light_brightness, 1.0f);
    //    negatif
    //    FragColor = vec4(vec3(1,1,1)-tex_color.xyz,tex_color.a); 
}
#endif