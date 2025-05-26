#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;
  
uniform mat4 projection_mat;

void main() {    
    gl_Position = projection_mat * (gl_in[0].gl_Position + vec4(-10.0, 0.0, 0.0, 0.0)); 
    EmitVertex();

    gl_Position = projection_mat * gl_in[0].gl_Position + vec4( 10.0, 0.0, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();

}    