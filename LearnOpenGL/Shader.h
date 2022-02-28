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
	Shader(const std::string& vertexShaderPath, const std::string fragmentShaderPath);
	~Shader();

private:
	std::string ReadShaderFromFile(const std::string& filePath);
	unsigned int CreateShader(const std::string& shaderSource, GLuint ShaderType);
	void CheckShader(unsigned int shaderID);
	unsigned int CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID);
	void CheckShaderProgram(unsigned int shaderProgramID);

public:
	void Bind() const;
	void Unbind() const;

private:
	int GetUniformLocation(const std::string& name);

public:
	void SetUniform4f(const std::string& name, float x, float y, float z, float w);
	void SetUniform1i(const std::string& name, int i);

	void SetUniformVec4(const std::string& name, const glm::vec4& vec);
	void SetUniformMat4(const std::string& name, const glm::mat4& mat);

private:
	unsigned int m_shaderProgramID;
	std::unordered_map<std::string, int> m_locationMap;
};

