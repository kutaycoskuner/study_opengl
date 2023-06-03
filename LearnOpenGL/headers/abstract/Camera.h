#pragma once
// ----- libraries
// ----------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix.h"


// ----- forward declarations
// ----------------------------------------------------------------------------

// ----- function declarations
// ----------------------------------------------------------------------------

// ----- abstract
// ----------------------------------------------------------------------------
struct Camera
{
public:
	Vec3 position;
	Vec3 target;
	Vec3 direction;
	float current_speed;

	Vec3 right;
	Vec3 up;
	Mat4 lookAt(const Vec3& new_pos, const Vec3& new_tar, const Vec3& new_up);
	Mat4 lookAt();

};