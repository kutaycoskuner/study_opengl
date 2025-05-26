// ----- notes
// ----------------------------------------------------------------------------

// ----- libraries
// ----------------------------------------------------------------------------
#include "utilities.h"				// self written utilities
#include "camera.h"				

// ----- function definitions
// ----------------------------------------------------------------------------
static Vec3 yawPitchToDirection(float yaw_rad, float pitch_rad)
{
	float yaw_deg = math_utils::toDegree(yaw_rad);
	float pitch_deg = math_utils::toDegree(pitch_rad);

	// in default (yaw=0, pitch=0) we are looking to		(1, 0, 0)
	// we need to rotate default view 90 toDegree to see	(0, 0, -1)

	/*
	In a right-handed 3D system, "yaw" typically refers to rotation around 
	the vertical (or up) axis. A positive yaw represents a rotation 
	to the right, and a negative yaw represents a rotation to the left. 
	This follows the right-hand rule where, if you extend your right hand 
	and curl your fingers in the direction of rotation, 
	your thumb points in the direction of the rotation axis. 
	*/

	// ----- test expectations
	// yaw 0, pitch 0
	// expected: x = 0, y = 0, z = -1
	//	
	// yaw 90, pitch 0 (turning around y axis 90 toDegree to right due to right hand rule)		
	// expected: x = 1, y = 0, z = 0
	// 
	// yaw 90, pitch 90
	// expected: x = 0, y = -1, z = 0
	//
	// yaw 45, pitch 45
	// sqrt(1 - (0.5**2 + 0.5**2))
	// expected: x = 0.5, y = -0.7, z = -.5
	//
	// yaw 30 pitch 60
	// expected: x = , y = sin(pitch), z =, 
	//
	// yaw 180 pitch 0
	// expected: x = 0, y = 0, z = 1
	//
	// yaw 180 pitch 180
	// expected x = 0, y = 0, z = -1
	//
	// reminder: cos 0 = 1, sin 0 = 0


	// ----- this one is default where yaw, pitch = 0, 0 targets (1, 0, 0)
	/*float x = cos(yaw_rad) * cos(pitch_rad);
	float y = sin(pitch_rad);
	float z = sin(yaw_rad) * cos(pitch_rad);*/
	
	float x = sin(yaw_rad) * cos(pitch_rad);
	float y = sin(pitch_rad);
	float z = - cos(yaw_rad) * cos(pitch_rad);


	// ----- uncomment to test below
	//float yaw_static = math_utils::toRadian(180.0f);
	//float pitch_static = math_utils::toRadian(180.0f);
	//x = sin(yaw_static) * cos(pitch_static);
	//y = -sin(pitch_static);
	//z = -cos(yaw_static) * cos(pitch_static);
	
	return Vec3(x, y, z).normalized();
} 

static void directionToYawPitch(const Vec3& direction, float& yaw_rad, float& pitch_rad)
{

	// Calculate yaw (left/right rotation)
	yaw_rad = std::atan2(direction.x, -direction.z);

	// Calculate pitch (up/down rotation)
	float lengthXZ = std::sqrt(direction.x * direction.x + direction.z * direction.z);
	pitch_rad = std::atan2(direction.y, lengthXZ);

	// direction.y		= sin(pitch_rad) =>
	// acos(direction.y)	= pitch_rad
	// testing
	//Vec3 norm = direction.normalized();
	//float pitch_deg = math_utils::toDegree(pitch_rad);
	//float yaw_deg	= math_utils::toDegree(yaw_rad);

}


void Camera::lookAtDirection(const Vec3& direction)
{
	directionToYawPitch(direction, this->yaw_rad, this->pitch_rad);
}

void Camera::lookAtTarget(const Vec3& target)
{
	Vec3 direction = (target - this->position).normalized();

	lookAtDirection(direction);
}



Mat4 Camera::calcViewMatrix(const Vec3& world_up) const
{
	Vec3 direction = -yawPitchToDirection(yaw_rad, pitch_rad);
	Vec3 right = getRight(world_up);
	Vec3 up = getUp(world_up);
	//getVectors(world_up);
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
	return 
		Mat4(
		 rx,  ry,  rz,  0,
		 ux,  uy,  uz,  0,
		 dx,  dy,  dz,  0,  // camera looking -z due to right hand rule therefore we negate direction
		  0,   0,   0,  1 
		) *
		Mat4(
			1, 0, 0, -px,
			0, 1, 0, -py,
			0, 0, 1, -pz,
			0, 0, 0, 1
		)
	;
}

void Camera::rotate(float x_offset, float y_offset)
{
	// 0,0 top left corner of the screen
	// mouse offset x right +	left -	| yaw
	// mouse offest y up    -	down +	| pitch
	// ----- description ^

	
	yaw_rad		-= x_offset;
	pitch_rad	-= y_offset;

	// Clamp pitch to avoid gimbal lock
    const float limit_rad = math_utils::toRadian(89.0f);  // just under 90°
    if (pitch_rad > limit_rad) pitch_rad = limit_rad;
    if (pitch_rad < -limit_rad) pitch_rad = -limit_rad;
}


Vec3 Camera::getDirection() const
{
	return yawPitchToDirection(yaw_rad, pitch_rad);
}

Vec3 Camera::getRight(const Vec3& world_up) const
{
		Vec3 forward = getDirection();
	Vec3 right = math_utils::cross3d(forward, world_up);

	// If forward and world_up are nearly parallel, use fallback axis (e.g., (0, 0, 1))
	if (right.lengthSquared() < 1e-6f) { // 0.000001f -> approximation to 0 limit due to float precision
		right = math_utils::cross3d(forward, Vec3(0, 0, 1));
	}
	return right.normalized();
}

Vec3 Camera::getUp(const Vec3& world_up) const
{
    Vec3 right = getRight(world_up);
    return math_utils::cross3d(right, getDirection()).normalized();
}

Mat4 Camera::getVectors(const Vec3& world_up) const
{
	Vec3 d = -getDirection();
	Vec3 r = getRight(world_up);
	Vec3 u = getUp(world_up);
	return Mat4(
		r.x, r.y, r.z, 0,
		u.x, u.y, u.z, 0,
		d.x, d.y, d.z, 0,
		  0,   0,   0, 1
	);
}