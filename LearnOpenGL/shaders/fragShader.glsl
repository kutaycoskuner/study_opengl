#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
    FragColor = ourColor;
} 