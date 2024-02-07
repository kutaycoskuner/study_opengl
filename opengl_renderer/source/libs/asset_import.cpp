// notes
// ---------------------------------------------------------------------------------------

// libraries
// ---------------------------------------------------------------------------------------
#include "../../headers/abstract/mesh.h"
#include "../../headers/abstract/model.h"
#include "../../headers/utils/utilities.h"

// function declarations
// ---------------------------------------------------------------------------------------


// function defintions
// ---------------------------------------------------------------------------------------
void Mesh::draw(Shader& shader)
{
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

void Mesh::setupMesh()
{
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

void Model::draw(Shader& shader)
{
    for (int ii = 0; ii < meshes.size(); ii++)
        meshes[ii].draw(shader);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    // ai = asset importer
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Error::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process all nodes meshes (if any)
    for (int ii = 0; ii < node->mNumMeshes; ii++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[ii]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // do the same for each of its children
    for (int ii = 0; ii < node->mNumChildren; ii++)
    {
        processNode(node->mChildren[ii], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (int ii = 0; ii < mesh->mNumVertices; ii++)
    {
        Vec3 vector;
        Vertex vertex;

        vector.x = mesh->mVertices[ii].x;
        vector.y = mesh->mVertices[ii].y;
        vector.z = mesh->mVertices[ii].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[ii].x;
        vector.y = mesh->mNormals[ii].y;
        vector.z = mesh->mNormals[ii].z;
        vertex.normal = vector;

        if (!mesh->mTextureCoords[0])
        {
            vertex.tex_coords = Vec2(0.0f, 0.0f);
        }
        else
        {
            Vec2 vector;
            vector.x = mesh->mTextureCoords[0][ii].x;
            vector.y = mesh->mTextureCoords[0][ii].y;
            vertex.tex_coords = vector;
        }
        
        // process vertex positions, normals and tex coords
        vertices.push_back(vertex);
    }

    // process indices if any
    for (int ii = 0; ii < mesh->mNumFaces; ii++)
    {
        aiFace face = mesh->mFaces[ii];
        for (int jj = 0; jj < face.mNumIndices; jj++)
            indices.push_back(face.mIndices[jj]);
    }
    
    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        //// 3. emissive maps
        std::vector<Texture> emissiveMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
        textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
        
        //// 3. normal maps
        //std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        //// 4. height maps
        //std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    return Mesh(vertices, indices, textures);

}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat,
    aiTextureType type, std::string type_name)
{
    std::vector<Texture> textures;

    for (int ii = 0; ii < mat->GetTextureCount(type); ii++)
    {
        aiString str;
        mat->GetTexture(type, ii, &str);
        bool skip = false;
        for (int jj = 0; jj < textures_loaded.size(); jj++)
        { 
            if (std::strcmp(textures_loaded[jj].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[jj]);
                skip = true;
                break;
            }
        }

        // load the texture if not already loaded
        if (!skip)
        {
            Texture texture;
            texture.id = img_utils::textureFromFile(str.C_Str(), this->directory);
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;

}

