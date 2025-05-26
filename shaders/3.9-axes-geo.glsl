#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 4) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

//out GS_OUT {
//    vec3 color
//} gs_out[];
//
const float MAGNITUDE = 0.2;


uniform mat4 view_mat;
uniform mat4 projection_mat;


void main()
{
    gl_Position =  projection_mat * view_mat * (gl_in[0].gl_Position + vec4(1000.0f, 0.0, 0.0, 0.0)); 
    EmitVertex();
    gl_Position = projection_mat * view_mat * (gl_in[0].gl_Position + vec4(-1000.0f, 0.0, 0.0, 0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position =  projection_mat * view_mat * (gl_in[0].gl_Position + vec4(0.0, 0.0, 1000.0f, 0.0)); 
    EmitVertex();
    gl_Position = projection_mat * view_mat * (gl_in[0].gl_Position + vec4(0.0, 0.0, -1000.0f, 0.0));
    EmitVertex();
    EndPrimitive();
}

