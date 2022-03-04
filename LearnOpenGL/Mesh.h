#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh
{
private:
	std::vector<struct Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<class Texture> m_textures;

	std::unique_ptr<class VertexBuffer> m_vertexBuffer;
	std::unique_ptr<class IndexBuffer> m_indexBuffer;
	std::unique_ptr<class VertexArray> m_vertexArray;
public:
	const class IndexBuffer& GetIndexBuffer() const { return *m_indexBuffer; }
	const class VertexArray& GetVertexArray() const { return *m_vertexArray; }
	const class std::vector<class Texture>& GetTextures() const { return m_textures; }

	Mesh(const std::vector<struct Vertex>& vertices, 
		const std::vector<unsigned int>& indices, 
		const std::vector<class Texture>& textures);

private:
	void SetupMesh();
};

