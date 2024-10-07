#version 330 core
out vec4 out_frag_color;

in vec3 v_normal;
in vec3 v_pos;

uniform vec3        view_pos;
uniform samplerCube skybox;

void main()
{
    // refraction ratio by snells law
    float refraction_ratio = 1.00 / 1.52;
    vec3 in_light    = normalize(v_pos - view_pos);
    // vec3 reflection  = reflect(in_light, normalize(v_normal));
    vec3 refraction = refract(in_light, normalize(v_normal), refraction_ratio);
    vec3 ref_light = refraction;
    out_frag_color = vec4(texture(skybox, ref_light).rgb, 1.0);
}