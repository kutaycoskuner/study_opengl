#version 330 core
#if 1
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;


void main()
{
    vec4 tex_color = texture(texture1, TexCoord);
    FragColor = FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor,1); 

    //    negatif
    //    FragColor = vec4(vec3(1,1,1)-tex_color.xyz,tex_color.a); 
    /*
        .55 .45 
    */
}
#endif