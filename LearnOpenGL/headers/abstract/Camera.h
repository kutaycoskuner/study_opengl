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
// todo: classs
struct Camera
{
public:
	// position
	Vec3 position;
	// axis
	Vec3 direction;
	Vec3 right;
	Vec3 up;
	// movement
	float current_speed;
	// angles
	float yaw;
	float pitch;

	// functions
	Mat4 calcViewMatrix(const Vec3& new_pos, const Vec3& new_tar, const Vec3& world_up);
	Mat4 calcViewMatrix();
	void calcAxes(const float& pitch, const float& yaw, const Vec3& world_up);
};