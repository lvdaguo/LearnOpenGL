#pragma once

#include <string>

/// <summary>
/// Œ∆¿Ì
/// </summary>
class Texture
{
public:
	Texture(const std::string& filepath, const std::string& type = "");
	Texture(const class Texture& other) = delete;
	class Texture& operator = (const class Texture& other) = delete;
	~Texture();

private:
	unsigned int m_textureID;
	int m_width, m_height;
	std::string m_type;

	void CreateTexture();
	void LoadTextureFromPicture(const std::string& filePath);

public:
	void Bind(unsigned int slot = 0) const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const std::string& GetType() const { return m_type; }
};

