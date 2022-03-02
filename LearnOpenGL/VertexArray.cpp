#include <glad/glad.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::AddLayout(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	this->Bind();
	vertexBuffer.Bind();
	auto& elements = layout.GetLayoutElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		auto& elem = elements[i];
		glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += elem.count * VertexBufferLayoutElement::GetSizeOfType(elem.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
}
