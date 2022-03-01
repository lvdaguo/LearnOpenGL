#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	// 传输数据
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	// 第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
	// GL_STATIC_DRAW  ：数据不会或几乎不会改变。
	// GL_DYNAMIC_DRAW ：数据会被改变很多。
	// GL_STREAM_DRAW  ：数据每次绘制时都会改变。
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}
