#include <glad/glad.h>
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexShaderPath, const std::string fragmentShaderPath)
{
	auto CreateShaderFromPath = [this](const std::string& filePath, GLuint shaderType)
	{
		std::string shaderSource = ReadShaderFromFile(filePath);
		return CreateShader(shaderSource, shaderType);
	};

	unsigned int vertexShaderID = CreateShaderFromPath(vertexShaderPath, GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = CreateShaderFromPath(fragmentShaderPath, GL_FRAGMENT_SHADER);

	m_shaderProgramID = CreateShaderProgram(vertexShaderID, fragmentShaderID);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderProgramID);
}

std::string Shader::ReadShaderFromFile(const std::string& filePath)
{
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		std::cout << filePath << "路径下的着色器读取成功" << std::endl;
		std::cout << shaderStream.str() << std::endl << std::endl;
		return shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << filePath << "路径下的着色器文件读取失败" << std::endl;
	}
}

unsigned int Shader::CreateShader(const std::string& shaderSource, GLuint ShaderType)
{
	unsigned int shaderID;
	shaderID = glCreateShader(ShaderType);

	const char* shaderSrc = shaderSource.c_str();
	glShaderSource(shaderID, 1, &shaderSrc, NULL);

	glCompileShader(shaderID);
	CheckShader(shaderID);

	return shaderID;
}

void Shader::CheckShader(unsigned int shaderID)
{
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = new char[length];
		glGetShaderInfoLog(shaderID, length, &length, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}
};

unsigned int Shader::CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID)
{
	unsigned int shaderProgramID;
	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	glLinkProgram(shaderProgramID);

	CheckShaderProgram(shaderProgramID);

	// 链接完成后，可释放单独shader的资源
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderProgramID;
}

void Shader::CheckShaderProgram(unsigned int shaderProgramID)
{
	int success;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = new char[length];
		glGetProgramInfoLog(shaderProgramID, length, &length, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}
};

void Shader::Bind() const
{
	glUseProgram(m_shaderProgramID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
	auto it = m_locationMap.find(name);
	int location = -1;
	if (it == m_locationMap.end())
	{
		location = glGetUniformLocation(m_shaderProgramID, name.c_str());
	}
	location = it->second;

	glUniform4f(m_shaderProgramID, x, y, z, w);
}
