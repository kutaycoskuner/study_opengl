#version 330 core
// notes
// ---------------------------------------------------------------------------------------
/*
    Shader name: draw ssao pass fragment shader

*/

out float f_frag_color;
  
in vec2 v_tex_coords;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D tex_noise;

uniform vec3 samples[64];

int kernel_size = 64;
float radius    = 0.5;
float bias      = 0.025;

// tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noise_scale = vec2(800.0/4.0, 600.0/4.0); 

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 view_proj_mat;

void main()
{             
    // input for ssao algorithm
    vec3 frag_pos   = texture(g_position, v_tex_coords).xyz;
    vec3 normal     = normalize(texture(g_normal, v_tex_coords).rgb);
    vec3 random_vec = normalize(texture(tex_noise, v_tex_coords * noise_scale).xyz);

    // create the tbn change of basis matrix: tangent space -> view space / gramm schmidt?
    vec3 tangent    = normalize(random_vec - normal * dot(random_vec, normal));
    vec3 bitangent  = cross(normal, tangent);
    mat3 tbn        = mat3(tangent, bitangent, normal);

    // iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    for (int i = 0; i < kernel_size; ++i)
    {
        // get sample position
        vec3 sample_pos = tbn * samples[i];
        sample_pos      = frag_pos + sample_pos * radius;

        // project sample position 
        vec4 offset = vec4(sample_pos, 1.0);
        offset = projection_mat * offset;           // view > clip space
        offset.xyz /= offset.w;                     // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5;        // transform to 0.0 - 1.0

        // get sample depth
        float sample_depth = texture(g_position, offset.xy).z;  // get depth value of the kernel sample 


        // todo inspect this algorithm
        // range check and accumulate: to remove too far occlusions
        float range_check = smoothstep(0.0, 1.0, radius / abs(frag_pos.z - sample_depth));
        occlusion += (sample_depth >= sample_pos.z + bias ? 1.0 : 0.0) * range_check;
    }

    occlusion = 1.0 - (occlusion / kernel_size);

    f_frag_color = occlusion;
    
}  