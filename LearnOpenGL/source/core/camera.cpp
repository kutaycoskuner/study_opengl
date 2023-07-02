// ----- notes
// ----------------------------------------------------------------------------

// ----- libraries
// ----------------------------------------------------------------------------
#include "../headers/utils/utilities.h"				// self written utilities
#include "../headers/abstract/camera.h"				


// ----- function definitions
// ----------------------------------------------------------------------------
void Camera::lookAt(const Vec3& new_pos, const Vec3& new_tar, const Vec3& world_up)
{
	position = new_pos;
	up = world_up;
	direction = (new_pos - new_tar).normalized();
	right = math_utils::cross3d(world_up, direction).normalized();
	up = math_utils::cross3d(direction, right).normalized();
}

Mat4 Camera::calcViewMatrix() const
{
	float rx = right.x;
	float ry = right.y;
	float rz = right.z;
	float ux = up.x;
	float uy = up.y;
	float uz = up.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;
	float px = position.x;
	float py = position.y;
	float pz = position.z;
	return Mat4(
		rx, ry, rz, 0,
		ux, uy, uz, 0,
		dx, dy, dz, 0,
		0, 0, 0, 1
	) *
		Mat4(
			1, 0, 0, -px,
			0, 1, 0, -py,
			0, 0, 1, -pz,
			0, 0, 0, 1
		);
}

void Camera::rotate(const float& pitch, const float& yaw, const Vec3& world_up)
{
	Vec3 new_dir;
	new_dir.x = cos(math_utils::radian(yaw)) * cos(math_utils::radian(pitch));
	new_dir.y = sin(math_utils::radian(pitch));
	new_dir.z = sin(math_utils::radian(yaw)) * cos(math_utils::radian(pitch));
	direction = new_dir.normalized();
	right = math_utils::cross3d(world_up, direction).normalized();
	up = math_utils::cross3d(direction, right).normalized();
}