#pragma once
// library
// ---------------------------------------------------------------------------------------
#include "../abstract/mesh.h"
#include "../abstract/shader.h"

#include "../../libs/assimp-5.2.5/config.h"

#include <vector>
#include <string>


// abstract
// ---------------------------------------------------------------------------------------
class Model
{
public:
	Model(char* path)
	{
		loadModel(path);
	}
	
	void draw(Shader& shader) {
		for (int ii = 0; ii < meshes.size(); ii++)
			meshes[ii].draw(shader);
	}

private:
	// model data
	std::vector<Mesh>	meshes;
	std::string			directory;

	void loadModel(std::string path);
	//void processNode(aiNode* node, const aiScene* scene);
	//Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
};