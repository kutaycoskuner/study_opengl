#pragma once



// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------

class VertexData;


// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

class VertexData
{
public:
	static float 		icosphere02__pos[720];
	static float 		icosahedron__pos[180];

	static float		origin[3];
	static float		skybox_vrts__pos[108];

	static float		cube_vrts__pos_uv[180];

	static float		cube_vrts__pos_norm_uv[288];
	static unsigned int cube_inds__pos_norm_uv[36];

	static float		plane_vrts__pos_tex[30];
	static float		plane_vrts__pos_norm_uv[48];
	static float		quad_vrts__pos_tex[24];	
	static float		quad_vrts__pos_norm_tex[42];
	static float		quad_vrts__pos_col[30];
    static float        quad__pos_uv[20];

	static float		square_vrts[32];
	static unsigned int square_inds[6];

	static float		x_axis[12];
	static float		y_axis[12];

	static float		rectangle__vrts[8]; 
};