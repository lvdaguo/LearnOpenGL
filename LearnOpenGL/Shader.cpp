#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string fragmentShaderPath, 
	const std::string& geometryShaderPath)
{
	auto CreateShaderFromPath = [this](const std::string& filePath, GLuint shaderType)
	{
		if (filePath == "") return static_cast<unsigned int>(0);
		std::string shaderSource = ReadShaderFromFile(filePath);
		return CreateShader(shaderSource, shaderType);
	};

	unsigned int vertexShaderID = CreateShaderFromPath(vertexShaderPath, GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = CreateShaderFromPath(fragmentShaderPath, GL_FRAGMENT_SHADER);
	unsigned int geometryShaderID = CreateShaderFromPath(geometryShaderPath, GL_GEOMETRY_SHADER);

	m_shaderProgramID = CreateShaderProgram(vertexShaderID, fragmentShaderID, geometryShaderID);
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

unsigned int Shader::CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID, 
	unsigned int geometryShaderID)
{
	unsigned int shaderProgramID;
	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	if (geometryShaderID != 0) glAttachShader(shaderProgramID, geometryShaderID);

	glLinkProgram(shaderProgramID);

	CheckShaderProgram(shaderProgramID);

	// 链接完成后，可释放单独shader的资源
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	if (geometryShaderID != 0) glDeleteShader(geometryShaderID);

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

void Shader::Use() const
{
	glUseProgram(m_shaderProgramID);
}

int Shader::GetUniformLocation(const std::string& name)
{
	auto it = m_locationMap.find(name);
	int location;
	if (it == m_locationMap.end())
	{
		location = glGetUniformLocation(m_shaderProgramID, name.c_str());
		m_locationMap.emplace(name, location);
	}
	else
	{
		location = it->second;
	}
	return location;
}

void Shader::SetFloat4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetFloat3(const std::string& name, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetFloat(const std::string& name, float f)
{
	glUniform1f(GetUniformLocation(name), f);
}

void Shader::SetInt(const std::string& name, int i)
{
	glUniform1i(GetUniformLocation(name), i);
}

void Shader::SetVector3(const std::string& name, const glm::vec3& vec)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::SetVector4(const std::string& name, const glm::vec4& vec)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
