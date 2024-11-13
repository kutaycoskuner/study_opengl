// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "data.h"     

// ----- data
// ------------------------------------------------------------------------------------------------
float VertexData::origin[] = {
    0.0f, 0.0f, 0.0f
};

float VertexData::skybox_vrts__pos[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

float VertexData::cube_vrts__pos_uv[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
     // Bottom face
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     // Top face
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};

float VertexData::plane_vrts__pos_tex[] = {
    // positions          // texture Coords 
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};
float VertexData::quad_vrts__pos_tex[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

float VertexData::quad_vrts__pos_norm_tex[] = { 
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f
};

float VertexData::quad_vrts__pos_col[] = {
    // positions      // colors
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
     0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};

float VertexData::cube_vrts__pos_norm_uv[] = {		  // position, normal, texture coords
    // Back face
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
	+0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
	+0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	+0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
    // Front face
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
    +0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 0.0f,
    +0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
    +0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
    // Left face
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
    // Right face
	+0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	+0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	+0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	+0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	+0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	+0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
    // Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
	+0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
	+0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	+0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
    // Top face
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
	+0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
	+0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	+0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f
};

float VertexData::plane_vrts__pos_norm_uv[] = {		// basic plane
    // pos, normal, uv
    -1.0f, -0.0f, -1.0f,    0.0f,  1.0f, 0.0f,	    0.0f, 0.0f,
    -1.0f, -0.0f, +1.0f,    0.0f,  1.0f, 0.0f,	    0.0f, 1.0f,
    +1.0f, -0.0f, +1.0f,    0.0f,  1.0f, 0.0f,	    1.0f, 1.0f,
    -1.0f, -0.0f, -1.0f,    0.0f,  1.0f, 0.0f,	    0.0f, 0.0f,
    +1.0f, -0.0f, +1.0f,    0.0f,  1.0f, 0.0f,	    1.0f, 1.0f,
    +1.0f, -0.0f, -1.0f,    0.0f,  1.0f, 0.0f,	    1.0f, 0.0f,
};

unsigned int VertexData::cube_inds__pos_norm_uv[] = {
     2,  1,  0,  5,  4,  3,     // back
     6,  7,  8,  9, 10, 11,     // front
    12, 13, 14, 15, 16, 17,     // left
    20, 19, 18, 23, 22, 21,     // right
    24, 25, 26, 27, 28, 29,     // bottom
    32, 31, 30, 35, 34, 33      // top
};


float VertexData::square_vrts[] = {
	// positions				// colors				// texture coords
	-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,				// top left 
	0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,				// top right 
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,				// bottom left 
	0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f				// bottom right 

};

unsigned int VertexData::square_inds[] = {
	0, 1, 2,	// first tri
	1, 2, 3		// second tri
};

float VertexData::x_axis[] = {
	// positions				// colors			
	-0.5f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,				// - 
	0.5f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f				// + 

};

float VertexData::y_axis[] = {
	// positions				// colors			
	0.0f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,				// -
	0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f				// + 

};

float VertexData::rectangle__vrts[] = {
    -0.5f,  0.5f, // top-left
     0.5f,  0.5f, // top-right
     0.5f, -0.5f, // bottom-right
    -0.5f, -0.5f  // bottom-left
};

//float vertices_v10[] = {
//	-0.5f, -0.5f, 0.0f,     // left
//	 0.5f, -0.5f, 0.0f,     // right
//	 0.0f,  0.5f, 0.0f      // top
//};
//
//float vertices_v11[] = {
//	// first triangle
//	-0.9f, -0.5f, 0.0f,  // left 
//	-0.0f, -0.5f, 0.0f,  // right
//	-0.45f, 0.5f, 0.0f,  // top 
//	// second triangle
//	 0.0f, -0.5f, 0.0f,  // left
//	 0.9f, -0.5f, 0.0f,  // right
//	 0.45f, 0.5f, 0.0f   // top 
//};
//
//float vertices[] = {
//	// positions           // colors
//	 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top 
//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
//	 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // bottom right
//};
//
//float texCoords[] = {
//	0.0f, 0.0f,  // lower-left corner  
//	1.0f, 0.0f,  // lower-right corner
//	0.5f, 1.0f   // top-center corner
//};
//
//
//float triangle1[] = {
//	// first triangle
//	-0.9f, -0.5f, 0.0f,  // left 
//	-0.0f, -0.5f, 0.0f,  // right
//	-0.45f, 0.5f, 0.0f,  // top  
//};
//
//
//float triangle2[] = {
//	// second triangle
//  0.0f, -0.5f, 0.0f,  // left
//  0.9f, -0.5f, 0.0f,  // right
//  0.45f, 0.5f, 0.0f   // top  
//};
//
//float vertices_2tri[] = {
//	// first triangle
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f,  0.5f, 0.0f,  // top left 
//	// second triangle
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f   // top left
//};
//
//float vertices_reduced[] = {
//	// first triangle
//	0.5f,  0.5f, 0.0f,   // top right
//	0.5f, -0.5f, 0.0f,   // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f   // top left
//};
//
//// to speciicy overlapping vertices | used with Element Buffer object
//unsigned int indices[] = {
//	0, 1, 3,    // first triangle
//	1, 2, 3     // second triangle
//};


