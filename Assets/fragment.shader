#version 330 core

out vec4 FragColor;
in vec3 Normals;
in vec3 FragPos;

uniform sampler2D ourTexture;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 color;
};

uniform vec3 viewPos;  
uniform Material material;
uniform Light lightMaterial;

void main()
{
	 vec3 ambient = material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightMaterial.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (lightMaterial.color *diff) * material.diffuse;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}