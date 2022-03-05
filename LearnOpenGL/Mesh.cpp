#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "VertexBufferLayout.h"

Mesh::Mesh(const std::vector<struct Vertex>& vertices, 
	const std::vector<unsigned int>& indices,
	const std::vector<std::shared_ptr<class Texture>>& textures) :
	m_textures(textures), m_vertexArray(), m_indexBuffer()
{
	SetupMesh(vertices, indices);
}

void Mesh::SetupMesh(const std::vector<struct Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], sizeof(struct Vertex) * vertices.size());
	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.Push<float>(3); // vertex.position
	vertexBufferLayout.Push<float>(3); // vertex.normal
	vertexBufferLayout.Push<float>(2); // vertex.texCoords

	m_vertexArray = std::make_unique<VertexArray>();
	m_vertexArray->AddLayout(*m_vertexBuffer, vertexBufferLayout);

	m_indexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());

	// vertexces 和 indices 在创建完VertexBuffer和IndexBuffer后即可删除，其数据已经传输到opengl缓冲内
}