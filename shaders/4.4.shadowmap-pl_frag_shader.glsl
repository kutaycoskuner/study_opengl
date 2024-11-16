#version 330 core
in vec4 g_world_position;

uniform vec3 light_position;
uniform float far_plane;


void main()
{
    // get distance between fragment and light source
//    vec4 new = g_world_position;
//    new.z = -new.z;
//    new = -new;
    float light_distance = length(g_world_position.xyz - light_position);

    
    // map to [0;1] range by dividing by far_plane
    light_distance = light_distance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = light_distance;
}  