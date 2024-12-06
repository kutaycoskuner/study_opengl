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
void Mesh::setDrawParameters(const Shader& shader)
{
	unsigned int num_diffuse = 0;
	unsigned int num_specular = 0;
	unsigned int num_normal = 0;
	unsigned int num_emissive = 0;
	for (int ii = 0; ii < textures.size(); ii++)
	{
		//glActiveTexture(GL_TEXTURE0 + ii);

		int texture_slot = -1;
		std::string name = textures[ii].type;
		if (name == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);
			name = "diffuse_map1";
			texture_slot = 0;
		}
		if (name == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1);
			name = "specular_map1";
			texture_slot = 1;
		}
		if (name == "texture_normal")
		{
			glActiveTexture(GL_TEXTURE2);
			name = "normal_map1";
			texture_slot = 2;
		}
		if (name == "texture_emissive")
		{
			glActiveTexture(GL_TEXTURE3);
			name = "emission_map1";
			texture_slot = 3;
		}
		if (texture_slot != -1)
		{
			shader.setInt(("material." + name).c_str(), texture_slot);
			glBindTexture(GL_TEXTURE_2D, textures[ii].id);
		}
	}

	glActiveTexture(GL_TEXTURE0);
	// draw vertex_array_name
	glBindVertexArray(vao);
}

void Mesh::draw(const Shader& shader)
{
	setDrawParameters(shader);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::drawInstanced(const Shader& shader, const unsigned int count)
{
	setDrawParameters(shader);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, count);
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
	// vertex texture coords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glBindVertexArray(0);
}

void Model::draw(const Shader& shader)
{
	for (int ii = 0; ii < meshes.size(); ii++)
		meshes[ii].draw(shader);
}

void Model::drawInstanced(const Shader& shader, const unsigned int count)
{
	for (int ii = 0; ii < meshes.size(); ii++)
		meshes[ii].drawInstanced(shader, count);
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	// ai = asset importer
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		//aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);
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

		Vec4 v4;
		v4.x = mesh->mTangents[ii].x;
		v4.y = mesh->mTangents[ii].y;
		v4.z = mesh->mTangents[ii].z;
		v4.w = 1.0f;
		vertex.tangent = v4;


		// Calculate bitangent handedness
		//if (mesh->mBitangents)
		//{
		//	// If Assimp provides bitangents, you can use them directly
		//	Vec3 bitangentFromAssimp;
		//	bitangentFromAssimp.x = mesh->mBitangents[ii].x;
		//	bitangentFromAssimp.y = mesh->mBitangents[ii].y;
		//	bitangentFromAssimp.z = mesh->mBitangents[ii].z;

		//	// Calculate handedness
		//	vertex.tangent.w = (
		//		math_utils::dot3d(
		//			math_utils::cross3d(
		//				vertex.normal,
		//				Vec3(vertex.tangent.x, vertex.tangent.y, vertex.tangent.z)
		//			), bitangentFromAssimp) < 0.0f) ? -1.0f : 1.0f;
		//}
		//else
		//{
		//    // If Assimp does not provide bitangents, calculate them using UV data
		//    Vec3 bitangentFromUV;

		//    // Assuming mTextureCoords[0] is not null
		//    if (!mesh->mTextureCoords[0])
		//    { 
		//        Vec2 uv0 = Vec2(mesh->mTextureCoords[0][ii].x, mesh->mTextureCoords[0][ii].y);
		//        Vec2 uv1 = Vec2(mesh->mTextureCoords[0][ii + 1].x, mesh->mTextureCoords[0][ii + 1].y);
		//        Vec2 uv2 = Vec2(mesh->mTextureCoords[0][ii + 2].x, mesh->mTextureCoords[0][ii + 2].y);
		//    }

		//    // Positions of vertices of a triangle
		//    Vec3 pos0 = Vec3(mesh->mVertices[ii].x, mesh->mVertices[ii].y, mesh->mVertices[ii].z);
		//    Vec3 pos1 = Vec3(mesh->mVertices[ii + 1].x, mesh->mVertices[ii + 1].y, mesh->mVertices[ii + 1].z);
		//    Vec3 pos2 = Vec3(mesh->mVertices[ii + 2].x, mesh->mVertices[ii + 2].y, mesh->mVertices[ii + 2].z);

		//    // Edges of the triangle
		//    Vec3 edge1 = pos1 - pos0;
		//    Vec3 edge2 = pos2 - pos0;

		//    // Delta UVs
		//    Vec2 deltaUV1 = uv1 - uv0;
		//    Vec2 deltaUV2 = uv2 - uv0;

		//    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		//    Vec3 tangent;
		//    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		//    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		//    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		//    tangent = vec_utils::normalize(tangent);

		//    bitangentFromUV.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		//    bitangentFromUV.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		//    bitangentFromUV.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		//    bitangentFromUV = vec_utils::normalize(bitangentFromUV);

		//    // Calculate handedness
		//    vertex.tangent.w = (
		//        math_utils::dot3d(
		//            math_utils::cross3d(
		//                vertex.normal, 
		//                tangent
		//            ), bitangentFromUV) < 0.0f) ? -1.0f : 1.0f;
		//}

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
		// 3. normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. emissive maps
		std::vector<Texture> emissiveMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
		textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());

		//if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		//    std::cout << "Diffuse textures found." << std::endl;
		//if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
		//    std::cout << "Specular textures found." << std::endl;
		//if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		//    std::cout << "Normal textures found." << std::endl;
		//if (material->GetTextureCount(aiTextureType_EMISSIVE) > 0)
		//    std::cout << "Emissive textures found." << std::endl;

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

