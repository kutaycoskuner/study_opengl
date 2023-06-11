#version 330 core
#if 1
out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;


void main()
{
    vec4 tex_color = texture(texture1, TexCoord);
    fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);// * vec4(ourColor,1); 
    fragColor = vec4(lightColor, 1.0f);
    //    negatif
    //    FragColor = vec4(vec3(1,1,1)-tex_color.xyz,tex_color.a); 
    /*
        .55 .45 
    */
}
#endif