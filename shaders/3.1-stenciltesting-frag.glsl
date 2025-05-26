#version 330 core
#if 1
// abstract
// ---------------------------------------------------------------------------------------
struct DirectionalLight {
   
   vec3 direction;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};

struct PointLight {    
   
   vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;  
};  

struct SpotLight {
    
    vec3 position;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
  
    float constant;
    float linear;
    float quadratic;

    float cutoff;
    float outer_cutoff;
};

struct Material {
    vec3 diffuse;
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_emissive1;
	vec3 specular;
    float emission_factor;
	float shininess;
};

struct Surface {

    vec3 normal;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
};

// globals = uniform variables
// ---------------------------------------------------------------------------------------
#define NR_POINT_LIGHTS 3
out vec4 f_frag_color;

in vec3 v_world_pos;

uniform vec3 view_pos;
uniform Material material;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;

float near  = 1.0f;
float far   = 100.0f;

// function definitons
// ---------------------------------------------------------------------------------------

// main
// ---------------------------------------------------------------------------------------
void main()
{
    // define output color value
//    vec3 illumination = vec3(0.9f);
    
    // blender selection color
    vec3 illumination = vec3(1.0f, 0.62f, 0.16f);
    


    f_frag_color = vec4(illumination, 1.0f);

}

#endif