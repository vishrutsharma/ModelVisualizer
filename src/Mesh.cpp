#include "Mesh.h"
#include <iostream>
#include "Scene.h"


Mesh::Mesh(const std::string& meshPath): VBO(0),VAO(0),EBO(0)
{
	C_Mesh::Data meshData = MeshLoader::LoadMesh(meshPath.c_str());
	if (!meshData.IsValid())
	{
		std::cout << "Does not have any Mesh Data" << std::endl;
		return;
	}

	m_data = std::move(meshData);

	std::vector<float> vertexData;
	for (const C_Graphics::Vertex& v : m_data.vertices)
	{
		glm::vec3 vertices = v.pos;
		glm::vec3 colors = v.colors;
		glm::vec2 uvs = v.uvs;
		glm::vec3 normals = v.normals;

		vertexData.push_back(vertices[0]);
		vertexData.push_back(vertices[1]);
		vertexData.push_back(vertices[2]);
		vertexData.push_back(colors[0]);
		vertexData.push_back(colors[1]);
		vertexData.push_back(colors[2]);
		vertexData.push_back(uvs[0]);
		vertexData.push_back(uvs[1]);
		vertexData.push_back(normals[0]);
		vertexData.push_back(normals[1]);
		vertexData.push_back(normals[2]);
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.indices.size() * sizeof(unsigned int), m_data.indices.data(), GL_STATIC_DRAW);

	int stride = 11 * sizeof(float); // 11 floats per vertex

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

}

void Mesh::Update()
{
	glm::vec3 pos = glm::vec3(5.0, 5.0, 5.0);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, pos);
	/*modelMatrix = glm::rotate(modelMatrix, rotation[0], glm::vec3(1.0, 0.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation[1], glm::vec3(0.0, 1.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation[2], glm::vec3(0.0, 0.0, 1.0));*/
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0,1.0,1.0));
	
	//Configure it inside Camera Class
	projectionMatrix = glm::perspective(glm::radians(45.0),840.0/840.0,0.1,100.0);

	unsigned int modelLocation = glGetUniformLocation(SHADER_ID, "model");
	unsigned int viewLocation = glGetUniformLocation(SHADER_ID, "view");
	unsigned int projectionLocation = glGetUniformLocation(SHADER_ID, "projection");
	glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glm::mat4 lookAtMat = glm::lookAt(pos, pos + glm::vec3(0, 0, -3.0), glm::vec3(0.0f, 1.0f, 0.0f));
	glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(lookAtMat));
	glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_data.indices.size(), GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}