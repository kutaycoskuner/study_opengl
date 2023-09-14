// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ----- data
// ------------------------------------------------------------------------------------------------
float ObjToDraw::cube_vrts__pos_uv[] = {
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

float ObjToDraw::cube_vrts__pos_norm_uv[] = {		  // position, normal, texture coords
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

unsigned int ObjToDraw::cube_inds__pos_norm_uv[] = {
     2,  1,  0,  5,  4,  3,     // back
     6,  7,  8,  9, 10, 11,     // front
    12, 13, 14, 15, 16, 17,     // left
    20, 19, 18, 23, 22, 21,     // right
    24, 25, 26, 27, 28, 29,     // bottom
    32, 31, 30, 35, 34, 33      // top
};


float ObjToDraw::square_vrts[] = {
	// positions				// colors				// texture coords
	-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,				// top left 
	0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,				// top right 
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,				// bottom left 
	0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f				// bottom right 

};

unsigned int ObjToDraw::square_inds[] = {
	0, 1, 2,	// first tri
	1, 2, 3		// second tri
};

float ObjToDraw::x_axis[] = {
	// positions				// colors			
	-0.5f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,				// - 
	0.5f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f				// + 

};

float ObjToDraw::y_axis[] = {
	// positions				// colors			
	0.0f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,				// -
	0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f				// + 

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


