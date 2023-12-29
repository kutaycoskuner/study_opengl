#pragma once
// library
// ---------------------------------------------------------------------------------------
#include "../abstract/mesh.h"
#include "../abstract/shader.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>


// abstract
// ---------------------------------------------------------------------------------------
class Model
{
public:
	// Default constructor
	Model() 
	{
	}

	// copy constructor
	Model(const Model& other)
	{
		// Perform a deep copy of the member variables
		meshes = other.meshes;
		textures_loaded = other.textures_loaded;
		directory = other.directory;
	}

	// parameter constructor
	Model(const char* path)
	{
		loadModel(path);
	}
	
	void draw(Shader& shader);

private:
	// model data
	std::vector<Mesh>		meshes;
	std::vector<Texture>	textures_loaded;
	std::string				directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
};

