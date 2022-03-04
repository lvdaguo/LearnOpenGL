#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filename, const std::string& directory, const std::string& type) :
	m_type(type)
{
	CreateTexture();
	stbi_set_flip_vertically_on_load(true);
	std::string filepath = directory + '/' + filename;
	LoadTextureFromPicture(filepath);
}

Texture::Texture(const Texture& other) :
	m_textureID(other.m_textureID), m_width(other.m_width),
	m_height(other.m_height), m_type(other.m_type) { }

//Texture::Texture(Texture&& other) noexcept :
//	m_width(other.m_width), m_height(other.m_height),
//	m_type(std::move(other.m_type)),
//	m_textureID(other.m_textureID)
//{
//	other.m_textureID = 0;
//}

Texture::~Texture()
{
	//if (m_textureID == 0) return;
	//glDeleteTextures(1, &m_textureID);
}

void Texture::CreateTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::LoadTextureFromPicture(const std::string& filePath)
{
	int channelCount;
	unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &channelCount, 0);
	if (data == nullptr)
	{
		std::cout << "加载纹理失败，路径为" << filePath << std::endl;
		stbi_image_free(data);
		return;
	}
	
	// std::string extension = GetFileExtension(filePath);
	/*
	GLenum channelType = 0;
	if      (extension == "png")	channelType = GL_RGBA;
	else if (extension == "jpg")    channelType = GL_RGB;
	else std::cout << "未定义的文件拓展名:\n" << extension << std::endl;
	*/

	GLenum channelType = 0;
	if (channelCount == 1) channelType = GL_RED;
	else if (channelCount == 3) channelType = GL_RGB;
	else if (channelCount == 4) channelType = GL_RGBA;
	else std::cout << "未定义的颜色通道数量: " << channelCount << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, channelType, m_width, m_height, 0, channelType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data); // 释放空间
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

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
