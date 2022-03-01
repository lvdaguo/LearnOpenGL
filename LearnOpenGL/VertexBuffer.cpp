#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	// ��������
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	// ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��
	// GL_STATIC_DRAW  �����ݲ���򼸺�����ı䡣
	// GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
	// GL_STREAM_DRAW  ������ÿ�λ���ʱ����ı䡣
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}
