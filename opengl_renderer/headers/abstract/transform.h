#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/matrix4.h"
#include <cmath>

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
struct Transform
{
public:
	Vec3 position;
	Vec3 rotation; // in degrees
	Vec3 scale;
    Vec3 dimensions; // in meter

    // Default constructor
    Transform()
        : position(Vec3(0.0f, 0.0f, 0.0f)), rotation(Vec3(0.0f, 0.0f, 0.0f)), scale(Vec3(1.0f, 1.0f, 1.0f)) {}

    // Parameterized constructor
    Transform(const Vec3& pos, const Vec3& rot, const Vec3& scl)
        : position(pos), rotation(rot), scale(scl) {}

    // Copy constructor
    Transform(const Transform& other)
        : position(other.position), rotation(other.rotation), scale(other.scale) {}

    // Getter methods
    //Vec3 getPosition() const { return position; }
    //Vec3 getRotation() const { return rotation; }
    //Vec3 getScale() const { return scale; }

    //// Setter methods
    //void setPosition(const Vec3& pos) { position = pos; }
    //void setRotation(const Vec3& rot) { rotation = rot; }
    //void setScale(const Vec3& scl) { scale = scl; }

    // Additional methods for updating the transformation
    void move(const Vec3& translation) { position += translation; }
    void rotate(const Vec3& rotationAnglesInDegree) {
        rotation.x = rotationAnglesInDegree.x / 360.0f;
        rotation.y = rotationAnglesInDegree.y / 360.0f;
        rotation.z = rotationAnglesInDegree.z / 360.0f;
    }
    //void scale(const Vec3& scale_factors) { 
    //    scale.x *= scale_factors.x; 
    //    scale.y *= scale_factors.y;
    //    scale.z *= scale_factors.z;
    //}

    // Placeholder for applying transformations using a 4x4 matrix
    Mat4 applyTransform() const {
        //return Mat4(); // Placeholder matrix for now
    }

};