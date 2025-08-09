#include "Model.h"
#include "Components.h"

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->Draw(shader);
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
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(ProcessMesh(mesh,scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<unsigned int> indices;
	std::vector<float> vertexData;
	C_Mesh::Data* meshData = new C_Mesh::Data();
	
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 normals = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		glm::vec2 uvCordinates;
		if (mesh->mTextureCoords[0])
		{
			uvCordinates = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			uvCordinates = glm::vec2(0, 0);
		
		meshData->vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		meshData->colors.push_back(glm::vec3(1.0, 1.0, 1.0));
		meshData->normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		meshData->uvs.push_back(uvCordinates);
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		meshData->indices = indices;
	}
	return new Mesh(meshData);
}

void Model::Update()
{

}
