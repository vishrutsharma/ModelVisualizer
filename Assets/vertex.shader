#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 uvs;
layout (location = 3) in vec3 vNormals;

out vec3 Normals;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Normals = mat3(model) * vNormals;
	FragPos = vec3(model * vec4(aPos,1.0));
	gl_Position =  projection * view * vec4(FragPos,1.0);
}