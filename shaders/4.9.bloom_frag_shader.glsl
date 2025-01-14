#version 330 core
#if 1
// notes
// ---------------------------------------------------------------------------------------
/*
    Shader name: bloom

*/

//layout (location = 0) out vec4 f_frag_color;
layout (location = 0) out vec4 f_bloom_color;  

// ---------------------------------------------------------------------------------------
//              globals = uniform variables
// ---------------------------------------------------------------------------------------
uniform sampler2D input_texture;
in vec2 v_tex_coords;

// ---------------------------------------------------------------------------------------
//              main
// ---------------------------------------------------------------------------------------
void main() {

    vec2 tex_coords = v_tex_coords;
    vec3 inp = vec3(texture(input_texture, tex_coords));


    // render target 1: bloom
    // check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(inp.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0)
        f_bloom_color = vec4(inp.rgb, 1.0);
    else
        f_bloom_color = vec4(0.0, 0.0, 0.0, 1.0);
}

#endif