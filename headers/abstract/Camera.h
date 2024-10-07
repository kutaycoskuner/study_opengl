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

	Camera()
		:rotation_sensitivity(0.002f)
		,aspect_ratio(1)
		,current_speed(1)
		,far(100.0f)
		,near(0.1f)
		,fov(60.0f)
		,pitch_rad(0.0f)
		,yaw_rad(0.0f)
		{}
};