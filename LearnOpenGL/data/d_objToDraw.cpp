// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ------------------------------------------------------------------------------------------------
// ----- Data
// ------------------------------------------------------------------------------------------------
float OpenGLParams::borderColor[] = {
	1.0f, 1.0f, 0.0f, 1.0f
};

float ObjToDraw::vertices[] = {
	// positions           // colors
	 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top 
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // bottom right
};

float vertices_v10[] = {
    -0.5f, -0.5f, 0.0f,     // left
     0.5f, -0.5f, 0.0f,     // right
     0.0f,  0.5f, 0.0f      // top
};

float vertices_v11[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	// second triangle
	 0.0f, -0.5f, 0.0f,  // left
	 0.9f, -0.5f, 0.0f,  // right
	 0.45f, 0.5f, 0.0f   // top 
};

float vertices[] = {
	// positions           // colors
	 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top 
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // bottom right
};

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};


float triangle1[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top  
};


float triangle2[] = {
	// second triangle
  0.0f, -0.5f, 0.0f,  // left
  0.9f, -0.5f, 0.0f,  // right
  0.45f, 0.5f, 0.0f   // top  
};

float vertices_2tri[] = {
	// first triangle
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f,  0.5f, 0.0f,  // top left 
	// second triangle
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
};

float vertices_reduced[] = {
	// first triangle
	0.5f,  0.5f, 0.0f,   // top right
	0.5f, -0.5f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
};

// to speciicy overlapping vertices | used with Element Buffer object
unsigned int indices[] = {
	0, 1, 3,    // first triangle
	1, 2, 3     // second triangle
};


