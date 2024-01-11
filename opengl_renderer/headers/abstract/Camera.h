#pragma once
// ----- libraries
// ----------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix4.h"


// ----- forward declarations
// ----------------------------------------------------------------------------

// ----- abstract
// ----------------------------------------------------------------------------
class Camera
{
public:
	// position
	Vec3 position;


	// angles from the world in toRadian
	float yaw_rad;
	float pitch_rad;

	// frustum
	float aspect_ratio;
	float near;
	float far;
	float fov;

	// movement
	float current_speed;
	float rotation_sensitivity;

	// functions
	void lookAtTarget(const Vec3& target);
	void lookAtDirection(const Vec3& direction);
	Mat4 calcViewMatrix(const Vec3& world_up) const;
	void rotate(float x_offset, float y_offset);

	Vec3 getDirection() const;
	Vec3 getRight(const Vec3& world_up) const;
	Vec3 getUp(const Vec3& world_up) const;

	Mat4 getVectors(const Vec3& world_up) const;
};