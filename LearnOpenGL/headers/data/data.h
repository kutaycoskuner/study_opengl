#pragma once
#ifndef D_DATA
#define D_DATA

class OpenGLParams
{
public:
    static float borderColor[4];
};

class ObjToDraw
{
public:
    static float cubeVrts[180];
    static float vertices[18];
    static float squareVrts[32];
    static unsigned int squareInds[6];
    static float x_axis[12];
    static float y_axis[12];
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
