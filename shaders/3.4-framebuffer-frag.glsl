#version 330 core
#if 1
in vec2 v_tex_coords;
out vec4 out_frag_color;

uniform sampler2D screen_texture;
uniform sampler2D screen_bloom;
uniform float exposure;
uniform bool bloom;

float Luma(vec3 color) { return max(dot(color, vec3(0.299, 0.587, 0.114)), 0.001); }

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
	vec3 hdr_color   = texture(screen_texture, v_tex_coords).rgb;

    if (bloom) 
    {
        vec3 bloom_color = texture(screen_bloom, v_tex_coords).rgb;
        hdr_color += bloom_color;
    }

    vec3 mapped = hdr_color;
    
    // tm: reinhard tone mapping 
    //    mapped = hdr_color / (hdr_color + vec3(1.0));
    
    // tm-alt: modified reinhard tone mapping 
    // mapped = hdr_color / (hdr_color + vec3(.5));
     mapped = vec3(1.0) - exp(-hdr_color * exposure);

    // tm-alt: linear tone mapping
    // tm-alt: logarithmic tone mapping
    // tm-alt: local tone mapping
    // tm-alt: bilateral filtering
    // tm-alt: gradient domain compression


    // gamma correction 
    mapped = linear_to_srgb(mapped);
    
    // output
    out_frag_color = vec4(mapped, 1.0f);

    //  0.0 disabled
    return;
	
	//   2.0 color inversion
	//	out_frag_color = vec4(vec3(1.0 - texture(screen_texture, v_tex_coords)), 1.0);

	//   3.0 grayscale
	//	float average = (out_frag_color.r + out_frag_color.g + out_frag_color.b) / 3.0;
	//   out_frag_color = vec4(average, average, average, 1.0);

	//   4.0 luminance
    //		float luma = Luma(out_frag_color.xyz);
    //		out_frag_color = vec4(luma, luma, luma, 1.0f);

	//   5.0 kernel
	const float offset = 1.0 / 300.0;  
	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    // 5.1 sharpen kernel
    //    float kernel[9] = float[](
    //        -1, -1, -1,
    //        -1,  9, -1,
    //        -1, -1, -1
    //    );

//    // 5.2 blur kernel
//    float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//    );
    

//    // 5.3 edge detection kernel
//    float kernel[9] = float[](
//    1.0, 1.0,   1.0,
//    1.0, -8.0,  1.0,
//    1.0, 1.0,   1.0
//    );
//
//    // 5.3 edge detection kernel
    float kernel[9] = float[](
    1.0, 1.0,   1.0,
    1.0, -8.0,  1.0,
    1.0, 1.0,   1.0
    );


    // 5.4 edge detection from gimp kernel
//    float kernel[9] = float[](
//    0.0, 1.0, 0.0,
//    1.0, -4.0, 1.0,
//    0.0, 1.0, 0.0
//    );
//
    // 5.5 edge detection
//    float kernel[9] = {
//        1,  2,  1,
//        2,  1,  2,
//        1,  2,  1
//    };

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screen_texture, v_tex_coords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    out_frag_color = vec4(col, 1.0);
}
#endif