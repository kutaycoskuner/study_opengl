#pragma once

#include "../abstract/vector3.h"

#include <vector>

// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

class Geometry
{
public:
	static void subdivide(const Vec3& v1, const Vec3& v2, const Vec3& v3,
		unsigned int level, std::vector<Vec3>& vertices, std::vector<int>& indices);
	static void generateIcosphere(unsigned int subdivisions);
	//static void subdivide();
};