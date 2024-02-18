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

void main()
{
    out_frag_color = mix(texture(texture1, v_tex_coord), texture(texture2, v_tex_coord), mix_val);
}
#endif