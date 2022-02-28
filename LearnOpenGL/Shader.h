#pragma once

#include <string>
#include <unordered_map>

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

	void SetUniform4f(const std::string& name, float x, float y, float z, float w);

private:
	unsigned int m_shaderProgramID;
	std::unordered_map<std::string, int> m_locationMap;
};

