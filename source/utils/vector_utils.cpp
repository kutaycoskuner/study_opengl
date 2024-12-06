// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../../headers/abstract/matrix4.h"
#include "../../headers/abstract/vector3.h"
#include "../../headers/abstract/vector4.h"
#include "../../headers/utils/utilities.h"
#include <cassert>
#include <cmath>

// ------------------------------------------------------------------------------------------------
// ----- Function Definitions
// ------------------------------------------------------------------------------------------------
namespace vec_utils
{
	float length(const Vec3& vec)
	{
		float result = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		return result;
	}

	float distance(const Vec3& vec1, const Vec3& vec2)
	{
		float x = vec1.x - vec2.x;
		float y = vec1.y - vec2.y;
		float z = vec1.z - vec2.z;

		Vec3 result_vector = Vec3(x, y, z);
		return length(result_vector);
	}

	Vec3 normalize(const Vec3& vec)
	{
		float len = length(vec);

		// Check to avoid division by zero
		if (len == 0.0f)
		{
			return Vec3(0.0f, 0.0f, 0.0f); // Return zero vector for zero-length vectors
		}

		return Vec3(vec.x / len, vec.y / len, vec.z / len);
	}

	//float mergeSort(std::vector<Vec3>& vec, bool is_ascending)
	//{
	//	if (vec.size() < 1)
	//		return;

	//	std::vector<Vec3> left = 
	//}
}