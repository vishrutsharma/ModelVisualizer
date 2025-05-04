#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <string>

class Model
{
public: 
	Model(char* path)
	{
		LoadModel(path);
	}
	void Draw(Shader& shader);

private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;

	void LoadModel(const char*);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};