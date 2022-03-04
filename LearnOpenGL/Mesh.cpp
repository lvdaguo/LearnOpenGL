#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "VertexBufferLayout.h"

Mesh::Mesh(const std::vector<struct Vertex>& vertices, 
	const std::vector<unsigned int>& indices,
	const std::vector<Texture>& textures) :
	m_vertices(vertices), m_indices(indices), m_textures(textures),
	m_vertexArray(), m_indexBuffer()
{
	SetupMesh();
}

void Mesh::SetupMesh()
{
	m_vertexBuffer = std::make_unique<VertexBuffer>(&m_vertices[0], sizeof(struct Vertex) * m_vertices.size());
	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.Push<float>(3); // vertex.position
	vertexBufferLayout.Push<float>(3); // vertex.normal
	vertexBufferLayout.Push<float>(2); // vertex.texCoords

	m_vertexArray = std::make_unique<VertexArray>();
	m_vertexArray->AddLayout(*m_vertexBuffer, vertexBufferLayout);

	m_indexBuffer = std::make_unique<IndexBuffer>(&m_indices[0], m_indices.size());
}