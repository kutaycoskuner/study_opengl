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
		compareApprox(m._11, 1.0f) &&
		compareApprox(m._12, 0.0f) &&
		compareApprox(m._22, 1.0f) &&
		compareApprox(m._32, 0.0f) &&
		compareApprox(m._44, 1.0f)
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

void unitTest_Mat4()
{
	unitTest_Mat4_defaultConstructor();
	unitTest_Mat4_paramConstructor();
	unitTest_Mat4_copyConstructor();

}
