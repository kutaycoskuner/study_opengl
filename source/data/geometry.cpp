#include "geometry.h" // data headers ex. model vertices

#include <string>
#include <iostream>

std::string formatFloat(float value) {
    return value == 0.0f ? "0.0f" : std::to_string(value) + "f";
}

void Geometry::subdivide(const Vec3& v1, const Vec3& v2, const Vec3& v3, unsigned int level, std::vector<Vec3>& vertices, std::vector<int>& indices)
{
    if (level == 0)
    {
        // Add the vertices of the triangle to the vertex array
        int startIdx = vertices.size();
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);

        // Add the indices of the triangle
        indices.push_back(startIdx);
        indices.push_back(startIdx + 1);
        indices.push_back(startIdx + 2);

        return;
    }

    // Calculate midpoints of each edge
    Vec3 mid1 = (v1 + v2) * 0.5f;
    Vec3 mid2 = (v2 + v3) * 0.5f;
    Vec3 mid3 = (v3 + v1) * 0.5f;

    // Normalize midpoints to fit the sphere
    mid1 = mid1.normalized();
    mid2 = mid2.normalized();
    mid3 = mid3.normalized();

    // Recursively subdivide each of the four new triangles
    subdivide(v1, mid1, mid3, level - 1, vertices, indices);
    subdivide(mid1, v2, mid2, level - 1, vertices, indices);
    subdivide(mid3, mid2, v3, level - 1, vertices, indices);
    subdivide(mid1, mid2, mid3, level - 1, vertices, indices);
}


void Geometry::generateIcosphere(unsigned int subdivisions)
{
    // Create the 12 vertices of an icosahedron
    const float X = 0.52573f;
    const float Z = 0.85065f;
    const Vec3 baseVertices[] = {
        {-X, 0.0f, Z}, {X, 0.0f, Z}, {-X, 0.0f, -Z},
        {X, 0.0f, -Z}, {0.0f, Z, X}, {0.0f, Z, -X},
        {0.0f, -Z, X}, {0.0f, -Z, -X}, {Z, X, 0.0f},
        {-Z, X, 0.0f}, {Z, -X, 0.0f}, {-Z, -X, 0.0f}
    };

    // Create the 20 triangular faces of the icosahedron
    const int baseIndices[] = {
        0, 4, 1, 0, 9, 4, 9, 5, 4, 4, 5, 8, 4, 8, 1,
        8, 10, 1, 8, 3, 10, 5, 3, 8, 5, 2, 3, 2, 7, 3,
        7, 10, 3, 7, 6, 10, 7, 11, 6, 11, 0, 6, 0, 1, 6,
        6, 1, 10, 9, 0, 11, 9, 11, 2, 9, 2, 5, 7, 2, 11
    };

    // Vector to store all vertices and indices
    std::vector<Vec3> vertices;
    std::vector<int> indices;

    // Add the base icosahedron
    for (int i = 0; i < 20; ++i)
    {
        Vec3 v1 = baseVertices[baseIndices[i * 3]];
        Vec3 v2 = baseVertices[baseIndices[i * 3 + 1]];
        Vec3 v3 = baseVertices[baseIndices[i * 3 + 2]];

        // Subdivide each face
        subdivide(v1, v2, v3, subdivisions, vertices, indices);
    }

    // Output the vertices and indices (optional, for debugging or visualization)
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        Vec3 v1 = vertices[indices[i]];
        Vec3 v2 = vertices[indices[i + 1]];
        Vec3 v3 = vertices[indices[i + 2]];

        std::cout << "// Face " << (i / 3 + 1) << "\n";
        std::cout << formatFloat(v1.x) << ", " << formatFloat(v1.y) << ", " << formatFloat(v1.z) << ", \n";
        std::cout << formatFloat(v2.x) << ", " << formatFloat(v2.y) << ", " << formatFloat(v2.z) << ", \n";
        std::cout << formatFloat(v3.x) << ", " << formatFloat(v3.y) << ", " << formatFloat(v3.z) << ", \n\n";
    }
}
