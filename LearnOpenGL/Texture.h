#pragma once

#include <string>

class Texture
{
public:
	// Texture(const std::string& path, const std::string& type = "");
	// Texture() { }
	Texture(const std::string& filename, const std::string& directory, const std::string& type = "");
	Texture(const class Texture& other);
	//Texture(class Texture&& other) noexcept;
	~Texture();

private:
	unsigned int m_textureID;
	int m_width, m_height;
	std::string m_type;

	void CreateTexture();
	void LoadTextureFromPicture(const std::string& filePath);
	std::string GetFileExtension(const std::string& filePath) const;

public:
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const std::string& GetType() const { return m_type; }
};

