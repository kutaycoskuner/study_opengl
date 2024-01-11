// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "../../headers/abstract/transform.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

// ---------------------------------------------------------------------------------------
// self keys
// ---------------------------------------------------------------------------------------
using namespace math_utils;


// ---------------------------------------------------------------------------------------
// forward declarations
// ---------------------------------------------------------------------------------------
void unitTest_Mat4();

// ---------------------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------------------
static void unitTest_Transform_defaultConstructor()
{
	Transform transform;
	assert(transform.position == Vec3(0.0f, 0.0f, 0.0f));
	assert(transform.rotation == Vec3(0.0f, 0.0f, 0.0f));
	assert(transform.scale == Vec3(1.0f, 1.0f, 1.0f));

}

static void unitTest_Transform_parameterConstructor()
{
	Transform transform(Vec3(1.0f, 2.0f, 3.0f), Vec3(4.0f, 5.0f, 6.0f), Vec3(7.0f, 8.0f, 9.0f));
	assert(transform.position == Vec3(1.0f, 2.0f, 3.0f));
	assert(transform.rotation == Vec3(4.0f, 5.0f, 6.0f));
	assert(transform.scale == Vec3(7.0f, 8.0f, 9.0f));

}

static void unitTest_Transform_copyConstructor()
{
	Transform transform1(Vec3(9.0f, 8.0f, 7.0f), Vec3(6.0f, 5.0f, 4.0f), Vec3(3.0f, 2.0f, 1.0f));
	Transform transform2 = transform1;
	assert(transform2.position == Vec3(9.0f, 8.0f, 7.0f));
	assert(transform2.rotation == Vec3(6.0f, 5.0f, 4.0f));
	assert(transform2.scale == Vec3(3.0f, 2.0f, 1.0f));

}

static void unitTest_Transform_getPosition()
{
	Transform transform1(Vec3(9.0f, 8.0f, 7.0f), Vec3(6.0f, 5.0f, 4.0f), Vec3(3.0f, 2.0f, 1.0f));
	Transform transform2 = transform1;
	assert(transform2.position == Vec3(9.0f, 8.0f, 7.0f));
}


void unitTest_Transform()
{
	// constuctors
	unitTest_Transform_defaultConstructor();
	unitTest_Transform_parameterConstructor();
	unitTest_Transform_copyConstructor();
	// functions

}
