#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/// <summary>
/// ¶¥µãÊý×é
/// </summary>
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddLayout(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_vertexArrayID;
};

