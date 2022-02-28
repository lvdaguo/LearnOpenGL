#include <glad/glad.h>
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& filePath)
{
	CreateTexture();
	
	stbi_set_flip_vertically_on_load(true);
	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &nrChannels, 0);
	if (data != nullptr)
	{
		std::string extension = GetFileExtension(filePath);
		if (extension == "png")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (extension == "jpg")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "未定义的文件拓展名:" << std::endl << extension << std::endl;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "加载纹理失败，路径为" << filePath << std::endl;
	}
	stbi_image_free(data); // 释放空间
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::CreateTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	//this->Bind(0);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::LoadTextureFromPicture(unsigned char* data, const std::string& filePath)
{
	if (data != nullptr)
	{
		std::string extension = GetFileExtension(filePath);
		if (extension == "png")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (extension == "jpg")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "未定义的文件拓展名:" << std::endl << extension << std::endl;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "加载纹理失败，路径为" << filePath << std::endl;
	}
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Texture::GetFileExtension(const std::string& filePath) const
{
	std::string extension;
	for (int i = filePath.length() - 1; i >= 0; --i)
	{
		if (filePath[i] == '.')
		{
			std::reverse(extension.begin(), extension.end());
			return extension;
		}
		extension.push_back(filePath[i]);
	}
	std::cout << filePath << "该文件路径找不到拓展名" << std::endl;
	return "";
}
