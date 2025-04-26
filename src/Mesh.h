#pragma once

#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include "Components.h"

class Mesh
{
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	C_Mesh::Data m_data;

public:
	Mesh(const std::string& meshPath);
	inline const C_Mesh::Data& GetData() { return m_data; }
	void Update();
	~Mesh();
};