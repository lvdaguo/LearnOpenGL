#pragma once

/// <summary>
/// ���㻺��
/// </summary>
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;

private:
	unsigned int m_bufferID;
};

