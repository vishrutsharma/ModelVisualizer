#include "Model.h"

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Draw(shader);
	}
}

void Model::LoadModel(const char* path)
{
	std::string  pString = std::string(path);
	Assimp::Importer importer;
	const aiScene* sceneOb = importer.ReadFile(pString, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!sceneOb || sceneOb->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !sceneOb->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_directory = pString.substr(0, pString.find_last_of('/'));
	ProcessNode(sceneOb->mRootNode, sceneOb);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{

}