#version 330 core
#if 1
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * world_matrix * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
#endif