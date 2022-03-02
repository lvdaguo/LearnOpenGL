#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	// specular
	float specularStrength = 0.7f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specular = specularStrength * material.specular * light.specular;

	// ambient
	vec3 ambient = material.ambient * light.ambient;

	vec3 result = diffuse + specular + ambient;
	FragColor = vec4(result, 1.0f);
}

// in vec2 TexCoord;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
// FragColor = vec4(objectColor * lightColor, 1.0f);