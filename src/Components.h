#pragma once
#include <glm.hpp>
#include <string>
#include <vector>

namespace C_Graphics
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 colors;
		glm::vec2 uvs;
		glm::vec3 normals;
	};
}

namespace C_Mesh
{
	struct Data
	{
		std::string name;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		bool IsValid() const {
			return !name.empty() && !vertices.empty() && !indices.empty();
		}
	};
}