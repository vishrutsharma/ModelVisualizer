#version 330 core

out vec4 FragColor;
in vec3 Normals;
in vec3 FragPos;
in vec3 VertexColor;

uniform vec3 viewPos;  

void main()
{
    FragColor = vec4(VertexColor, 1.0);
}