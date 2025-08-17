#include "Mesh.h"
#include <iostream>
#include "Scene.h"


Mesh::Mesh(C_Mesh::Data* data): m_data(data), VBO(0),VAO(0),EBO(0)
{
	std::vector<float> verticesData;
	for (int i = 0; i < m_data->vertices.size(); i++)
	{
		verticesData.push_back(m_data->vertices[i].x);
		verticesData.push_back(m_data->vertices[i].y);
		verticesData.push_back(m_data->vertices[i].z);

		verticesData.push_back(m_data->colors[i].x);
		verticesData.push_back(m_data->colors[i].y);
		verticesData.push_back(m_data->colors[i].z);

		verticesData.push_back(m_data->uvs[i].x);
		verticesData.push_back(m_data->uvs[i].y);

		verticesData.push_back(m_data->normals[i].x);
		verticesData.push_back(m_data->normals[i].y);
		verticesData.push_back(m_data->normals[i].z);
	}
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(float), verticesData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data->indices.size() * sizeof(unsigned int), m_data->indices.data(), GL_STATIC_DRAW);

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
	glm::vec3 pos = this->GetPosition();
	glm::vec3 rotation = this->GetRotation();
	glm::vec3 scale = this->GetScale();
	
	glm::mat4 modelMatrix = glm::mat4(1.0);
	glm::mat4 viewMatrix = glm::mat4(1.0);
	glm::mat4 projectionMatrix = glm::mat4(1.0);

	modelMatrix = glm::translate(modelMatrix,pos);
	modelMatrix = glm::rotate(modelMatrix, rotation[0], glm::vec3(1.0, 0.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation[1], glm::vec3(0.0, 1.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, rotation[2], glm::vec3(0.0, 0.0, 1.0));
	modelMatrix = glm::scale(modelMatrix, scale);

	viewMatrix = glm::lookAt(pos, pos + glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 1.0, 0.0));
	projectionMatrix = glm::perspective(glm::radians(45.0),840.0/840.0,0.1,100.0);

	unsigned int modelLocation = glGetUniformLocation(SHADER_ID, "model");
	unsigned int viewLocation = glGetUniformLocation(SHADER_ID, "view");
	unsigned int projectionLocation = glGetUniformLocation(SHADER_ID, "projection");

	glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_data->indices.size(), GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}