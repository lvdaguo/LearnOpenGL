#pragma once

/// <summary>
/// ¶¥µãÊý×é
/// </summary>
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddLayout(const class VertexBuffer& vertexBuffer, const class VertexBufferLayout& vertexBufferLayout);

	void Bind() const;

private:
	unsigned int m_vertexArrayID;
};

