#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 tex_coords;
    vec3 normal;
} gs_in[];

out vec2 tex_coords; 
out vec3 g_normals;
uniform float time;
uniform float anim_tant;




vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction;
    float frequency = anim_tant;


    direction = normal * frequency; 

    return position + vec4(direction, 0.0);
}



vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    g_normals = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, g_normals);
    tex_coords = gs_in[0].tex_coords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, g_normals);
    tex_coords = gs_in[1].tex_coords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, g_normals);
    tex_coords = gs_in[2].tex_coords;
    EmitVertex();
    EndPrimitive();
}