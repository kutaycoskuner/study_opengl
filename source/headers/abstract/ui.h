#pragma once
#include "../abstract/vector3.h" 
#include "../abstract/vector4.h" 

struct UIState
{
	int width		= 800;
	int height		= 600;
	float near		= 0.1f;
	float far		= 100.0f;
	float top		= 0.0f;
	float left		= 0.0f;
	bool animate	= false;
	Vec4 clear_color;
};