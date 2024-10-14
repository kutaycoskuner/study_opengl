#version 330 core
#if 1
// abstract
// ---------------------------------------------------------------------------------------
struct Material {
    
    sampler2D diffuse_map;
};

struct Surface {

    vec3 normal;
    vec3 diffuse;
    vec4 diffuse4;
    vec3 specular;
    vec3 emissive;
};

// globals = uniform variables
// ---------------------------------------------------------------------------------------
#define NR_POINT_LIGHTS 3
out vec4 f_frag_color;

in vec3 v_normal;  
in vec3 v_world_pos;
in vec2 v_tex_coords;

uniform vec3 view_pos;
uniform Material material;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;

// function definitons
// ---------------------------------------------------------------------------------------

// main
// ---------------------------------------------------------------------------------------
void main()
{

    vec4 output_test    = texture(material.diffuse_map, v_tex_coords);
    
    // remove transparent
    if (output_test.a < 0.1f)
        discard;
    
    // result
    f_frag_color = output_test;
}

#endif