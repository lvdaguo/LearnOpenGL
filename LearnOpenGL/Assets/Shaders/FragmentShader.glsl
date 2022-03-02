#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	// vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

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
	// vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;
	// vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * light.specular;

	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	float distance = length(lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-light.direction));

	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 result;
	result = diffuse + specular + ambient;
	result *= attenuation;
	result *= intensity;

	// if (theta > light.cutOff) {
	// } else {
	//	result = light.ambient * vec3(texture(material.diffuse, TexCoords));
	// }
	// vec3 result = diffuse + specular + ambient;

	// result *= attenuation;
	FragColor = vec4(result, 1.0f);
}