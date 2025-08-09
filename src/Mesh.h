#pragma once

#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include "Components.h"
#include "Shader.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class Mesh
{
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int SHADER_ID;
	C_Mesh::Data* m_data;
	glm::vec3 position;

public:
	Mesh(C_Mesh::Data*);
	//inline const C_Mesh::Data& GetData() { return m_data; }
	void Draw(Shader& shader);
	void Update();
	~Mesh();
};