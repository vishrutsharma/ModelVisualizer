#pragma once
#include <glm.hpp>
#include <string>
#include <vector>

namespace C_Mesh
{
	struct Data
	{
		std::string name;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;

		bool IsValid() const {
			return !name.empty() && !vertices.empty() && !indices.empty();
		}
	};
}