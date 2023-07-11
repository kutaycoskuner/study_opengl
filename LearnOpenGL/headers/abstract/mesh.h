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
	unsigned int id;
	std::string type;
};


class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }
    void draw(Shader& shader) {
        unsigned int num_diffuse = 1;
        unsigned int num_specular = 1;
        for (int ii = 0; ii < textures.size(); ii++)
        {
            glActiveTexture(GL_TEXTURE0 + ii);
            
            std::string number;
            std::string name;
            if (name == "texture_diffuse")
                number = std::to_string(num_diffuse += 1);
            if (name == "texture_specular")
                number = std::to_string(num_specular += 1);
            
            shader.setInt(("material." + name + number).c_str(), ii);
            glBindTexture(GL_TEXTURE_2D, textures[ii].id);
        }

        glActiveTexture(GL_TEXTURE0);
        
        // draw mesh
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    //  render data
    unsigned int vao, vbo, ebo;

    void setupMesh() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

        glBindVertexArray(0);
    }
};

#endif
