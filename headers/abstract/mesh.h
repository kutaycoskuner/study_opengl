#pragma once
#ifndef MESH_H
#define MESH_H
// ----- libraries
// ---------------------------------------------------------------------------------------
#include "../abstract/vector3.h"
#include "../abstract/vector2.h"
#include "../abstract/shader.h"
#include <string>
#include <vector>

// ----- abstract
// ---------------------------------------------------------------------------------------
struct Vertex
{
	// will be removed as it will not be necessary on directional light model
	Vec3 position;
	Vec3 normal;
	Vec2 tex_coords;
};

struct Texture {
	unsigned int id    = 0;
	std::string type;
    std::string path;  // store path of the texture to compare with other textures to avoid redundant work
};


class Mesh {
public:
    // vertex_array_name data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    // parameter constructor
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    void draw(const Shader& shader);
    void drawInstanced(const Shader& shader, const unsigned int count);

    unsigned int vao, vbo, ebo;
private:
    //  render data

    void setupMesh();
};

#endif
