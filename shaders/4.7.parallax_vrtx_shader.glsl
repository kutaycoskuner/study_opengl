    #version 330 core
    #if 1
    layout (location = 0) in vec3 in_position;
    layout (location = 1) in vec3 in_normal;
    layout (location = 2) in vec2 in_tex_coords;
    layout (location = 3) in vec4 in_tangent;
    // layout (location = 4) in vec3 in_bitangent;

    out VS_OUT {
        vec3 world_position;
        vec3 world_normal;
        vec2 tex_coords;
        mat3 tbn;
    } vs_out;

    uniform mat4 world_mat;
    uniform mat4 projection_mat;
    uniform mat4 view_mat;

    void main()
    {    
        // world = local > world
        // 
        vs_out.world_position         = vec3(world_mat * vec4(in_position, 1.0));
        vs_out.tex_coords             = in_tex_coords;

        mat3 normal_mat               = transpose(inverse(mat3(world_mat))); 
									    // mat3 is selecting sub 3x3 sub matrix of 4x4 means that discards translation as translation embedded on last column
									    // inverse discarding both rotation and scale.
									    // transpose bringing rotation back
									    // result: retrieving only the rotation 
        vec3 tangent                  = normalize(normal_mat * in_tangent.xyz);
        vec3 normal                   = normalize(normal_mat * in_normal);

        // re-orthogonalize T with respect to N (Gram-Schmidt process)
        tangent                       = normalize(tangent - dot(tangent,normal) * normal);

        // Handle bitangent handedness
        float handedness              = in_tangent.w; // Extract w component as handedness (+1 or -1)
        vec3 bitangent                = cross(normal, tangent) * handedness;
        
        // debug
//       tangent   = vec3(1.0, 0.0, 0.0);
//       bitangent = vec3(0.0, 1.0, 0.0);
//       normal    = vec3(0.0, 0.0, 1.0);

        // tangent, bitangent, normal matrix
        // transpose -> orthogonal matrislerdeki bir ozellikten oturu inverse yapiyor.
        // inverse matris tangenttan worlde gecirmek yerine world den tangenta geciriyor
        vs_out.tbn                     = transpose(mat3(tangent, bitangent, normal));
//        vs_out.tbn                     = mat3(tangent, bitangent, normal);
        vs_out.world_normal            = normal;

        gl_Position                    = projection_mat * view_mat * vec4(vs_out.world_position, 1.0);
    }

    #endif