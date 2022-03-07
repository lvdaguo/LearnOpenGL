#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

/// <summary>
/// ×ÅÉ«Æ÷
/// </summary>
class Shader
{
public:
	Shader(const std::string& vertexShaderPath, const std::string fragmentShaderPath, 
		const std::string& geometryShaderPath = "");
	Shader(const class Shader& other) = delete;
	class Shader& operator = (const class Shader& other) = delete;
	~Shader();

private:
	std::string ReadShaderFromFile(const std::string& filePath);
	unsigned int CreateShader(const std::string& shaderSource, GLuint ShaderType);
	void CheckShader(unsigned int shaderID);
	unsigned int CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID, 
		unsigned int geometryShaderID);
	void CheckShaderProgram(unsigned int shaderProgramID);

public:
	void Use() const;

private:
	int GetUniformLocation(const std::string& name);

public:
	void SetFloat4(const std::string& name, float x, float y, float z, float w);
	void SetFloat3(const std::string& name, float x, float y, float z);
	void SetFloat(const std::string& name, float f);
	void SetInt(const std::string& name, int i);

	void SetVector3(const std::string& name, const glm::vec3& vec);
	void SetVector4(const std::string& name, const glm::vec4& vec);
	void SetMatrix4(const std::string& name, const glm::mat4& mat);

private:
	unsigned int m_shaderProgramID;
	std::unordered_map<std::string, int> m_locationMap;

public:
	unsigned int GetID() const { return m_shaderProgramID; }
};

