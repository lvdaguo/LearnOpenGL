#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

private:
	unsigned int m_textureID;
	int m_width, m_height;

	void LoadTextureFromPicture(unsigned char* data, const std::string& filePath);
	void CreateTexture();
	std::string GetFileExtension(const std::string& filePath) const;

public:
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
};

