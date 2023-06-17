#pragma once
#ifndef D_DATA
#define D_DATA
#include "../abstract/material.h"

class OpenGLParams
{
public:
	static float borderColor[4];
};

class ObjToDraw
{
public:
	static float cubeVrts[180];
	static float lightCubeVrts[288];
	static float vertices[18];
	static float squareVrts[32];
	static unsigned int squareInds[6];
	static float x_axis[12];
	static float y_axis[12];
};

class PresetMaterial
{
public:
	static const Material emerald;
	static const Material jade;
	static const Material obsidian;
	static const Material pearl;
	static const Material ruby;
	static const Material turquoise;
	static const Material brass;
	static const Material bronze;
	static const Material chrome;
	static const Material copper;
	static const Material gold;
	static const Material silver;
	static const Material black_plastic;
	static const Material cyan_plastic;
	static const Material green_plastic;
	static const Material red_plastic;
	static const Material white_plastic;
	static const Material yellow_plastic;
	static const Material black_rubber;
	static const Material cyan_rubber;
	static const Material green_rubber;
	static const Material red_rubber;
	static const Material white_rubber;
	static const Material yellow_rubber;
};

// extern float vertices[18];
//
// extern float triangle1[9];
// extern float triangle2[9];
//
// extern float vertices_2tri[18];
// extern float vertices_reduced[12];
// extern unsigned int indices[6];

#endif
