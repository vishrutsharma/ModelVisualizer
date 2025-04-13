#pragma once
#include <vector>
#include <glm.hpp>
#include <memory>

namespace Objects
{
	struct Node
	{
		std::vector<std::unique_ptr<Node>> childrens;
		std::vector<unsigned int> mesheIndices;
	};

	struct SceneObject
	{
		std::unique_ptr<Node> rootNode = std::make_unique<Node>();
		std::vector<Mesh> meshes;
		std::vector<Material> materials;
	};	

	struct Mesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> tCoordinates;
		std::vector<Face> faces;
		unsigned int materialIndex;
	};

	struct Material
	{

	};

	struct Face
	{
		std::vector<unsigned int> indices;
	};
}