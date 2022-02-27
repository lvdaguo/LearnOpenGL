#pragma once

#include <string>

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
	void Bind();
	void Unbind();

private:
	unsigned int m_shaderProgramID;
};

