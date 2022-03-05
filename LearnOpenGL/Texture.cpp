#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filepath, const std::string& type)
{
	CreateTexture();
	stbi_set_flip_vertically_on_load(true);
	LoadTextureFromPicture(filepath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
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
	
	GLenum channelType = 0;
	if (channelCount == 1) channelType = GL_RED;
	else if (channelCount == 3) channelType = GL_RGB;
	else if (channelCount == 4) channelType = GL_RGBA;
	else std::cout << "未定义的颜色通道数量: " << channelCount << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, channelType, m_width, m_height, 0, channelType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data); // 释放空间
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}