#pragma once
#include "../abstract/vector4.h" 

struct UIState
{
	int width, height;
	float near, far;
	float top, left;
	bool animate;
	Vec4 clear_color;
};