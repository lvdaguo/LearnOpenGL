#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

private:
	unsigned int m_bufferID;
};

