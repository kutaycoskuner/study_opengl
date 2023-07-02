#pragma once
// ----- libraries
// ----------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix4.h"


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

	// frustum
	float aspect_ratio;
	float near;
	float far;
	float fov;

	// movement
	float current_speed;

	// angles from word
	float yaw;
	float pitch;

	// functions
	Mat4 calcViewMatrix() const;
	void rotate(const float& pitch, const float& yaw, const Vec3& world_up);
	void lookAt(const Vec3& new_pos, const Vec3& new_tar, const Vec3& world_up);
};