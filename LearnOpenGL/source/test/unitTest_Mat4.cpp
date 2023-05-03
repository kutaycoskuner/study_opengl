// lib
#include "../../headers/abstract/matrix.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

// self keys
using namespace math_utils;


// pre
void unitTest_Mat4();

// functions
static void unitTest_Mat4_defaultConstructor()
{
	Mat4 m;
	assert(
		compareApprox(m._11, 0.0f) &&
		compareApprox(m._12, 0.0f) &&
		compareApprox(m._22, 0.0f) &&
		compareApprox(m._32, 0.0f) &&
		compareApprox(m._44, 0.0f)
	);
}

static void unitTest_Mat4_paramConstructor()
{
	Mat4 m(4);
	float param = 4.0f;
	assert(
		compareApprox(m._11, param) && compareApprox(m._12, param) && compareApprox(m._13, param) && compareApprox(m._14, param) &&
		compareApprox(m._21, param) && compareApprox(m._22, param) && compareApprox(m._23, param) && compareApprox(m._24, param) &&
		compareApprox(m._31, param) && compareApprox(m._32, param) && compareApprox(m._33, param) && compareApprox(m._34, param) &&
		compareApprox(m._41, param) && compareApprox(m._42, param) && compareApprox(m._43, param) && compareApprox(m._44, param)
	);

}

static void unitTest_Mat4_copyConstructor()
{
	float param = 5.0f;
	Mat4 m_b(param);			// blueprint
	Mat4 m_c(m_b);				// copy
	assert(m_c._11 == param);
}

static void unitTest_Mat4_negation()
{
	Mat4 a(3);
	Mat4 b = -a;
	assert(b.m[0][0] == -3.0f);
}

static void unitTest_Mat4_addition()
{
	Mat4 a(3);
	Mat4 b(2);
	Mat4 c = a + b;
	assert(c._11 == 5.0f);
}

static void unitTest_Mat4_subtraction()
{
	Mat4 a(3);
	Mat4 b(2);
	Mat4 c = a - b;
	assert(c.m[0][0] == 1.0f);
}

static void unitTest_Mat4_scalar_product()
{
	Mat4 a(3);
	float b = 2;
	Mat4 c = a * b;
	assert(c.m[0][0] == 6.0f);
}

static void unitTest_Mat4_mat4_product()
{
	Mat4 a( 4, 2, 0, 0, 
			0, 8, 1, 0, 
			0, 1, 0, 0, 
			0, 0, 0, 1);
	
	Mat4 b( 4, 2, 1, 0,
		    2, 0, 4, 0,
			9, 4, 2, 0,
			0, 0, 0, 1);
	
	Mat4 c = a * b;
	assert(
		c.m[0][0] == 20 && c.m[0][1] == 8  && c.m[0][2] == 12 && c.m[0][3] == 0 &&
		c.m[1][0] == 25 && c.m[1][1] == 4  && c.m[1][2] == 34 && c.m[1][3] == 0 &&
		c.m[2][0] == 2  && c.m[2][1] == 0  && c.m[2][2] == 4  && c.m[2][3] == 0 &&
		c.m[3][0] == 0  && c.m[3][1] == 0  && c.m[3][2] == 0  && c.m[3][3] == 1 
	);
}

void unitTest_Mat4()
{
	unitTest_Mat4_defaultConstructor();
	unitTest_Mat4_paramConstructor();
	unitTest_Mat4_copyConstructor();
	unitTest_Mat4_negation();
	unitTest_Mat4_addition();
	unitTest_Mat4_subtraction();
	unitTest_Mat4_scalar_product();
	unitTest_Mat4_mat4_product();
}
