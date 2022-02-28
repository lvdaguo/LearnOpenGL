#include <glad/glad.h>
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& filePath)
{
	CreateTexture();
	stbi_set_flip_vertically_on_load(true);
	LoadTextureFromPicture(filePath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::CreateTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::LoadTextureFromPicture(const std::string& filePath)
{
	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &nrChannels, 0);
	if (data == nullptr)
	{
		std::cout << "��������ʧ�ܣ�·��Ϊ" << filePath << std::endl;
		stbi_image_free(data);
		return;
	}
	
	std::string extension = GetFileExtension(filePath);

	GLenum channelType = 0;
	if      (extension == "png")	channelType = GL_RGBA;
	else if (extension == "jpg")    channelType = GL_RGB;
	else std::cout << "δ������ļ���չ��:\n" << extension << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, channelType, m_width, m_height, 0, channelType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data); // �ͷſռ�
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
	std::cout << filePath << "���ļ�·���Ҳ�����չ��" << std::endl;
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
