// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ------------------------------------------------------------------------------------------------
// ----- Dat0a
// ------------------------------------------------------------------------------------------------

//float vertices[] = {
//    -0.5f, -0.5f, 0.0f,     // left
//     0.5f, -0.5f, 0.0f,     // right
//     0.0f,  0.5f, 0.0f      // top
//};

float vertices[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	// second triangle
	 0.0f, -0.5f, 0.0f,  // left
	 0.9f, -0.5f, 0.0f,  // right
	 0.45f, 0.5f, 0.0f   // top 
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