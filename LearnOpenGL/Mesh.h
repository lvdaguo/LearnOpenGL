#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

/// <summary>
/// 顶点（纯数据结构体）
/// </summary>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

/// <summary>
/// 网格
/// </summary>
class Mesh
{
public:
	Mesh(const std::vector<struct Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<std::shared_ptr<class Texture>>& textures);

private:
	std::vector<std::shared_ptr<class Texture>> m_textures;

	std::unique_ptr<class VertexBuffer> m_vertexBuffer;
	std::unique_ptr<class IndexBuffer> m_indexBuffer;
	std::unique_ptr<class VertexArray> m_vertexArray;

public:
	const class IndexBuffer& GetIndexBuffer() const { return *m_indexBuffer; }
	const class VertexArray& GetVertexArray() const { return *m_vertexArray; }
	const class std::vector<std::shared_ptr<class Texture>>& GetTextures() const { return m_textures; }

private:
	void SetupMesh(const std::vector<struct Vertex>& vertices, const std::vector<unsigned int>& indices);
};

