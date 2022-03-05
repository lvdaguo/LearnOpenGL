#pragma once

/// <summary>
/// ���㻺��
/// </summary>
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const class VertexBuffer& other) = delete;
	class VertexBuffer operator = (const class VertexBuffer& other) = delete;
	~VertexBuffer();

	void Bind() const;

private:
	unsigned int m_bufferID;
};

