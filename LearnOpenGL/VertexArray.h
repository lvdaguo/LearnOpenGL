#pragma once

/// <summary>
/// 顶点数组
/// （维护了顶点缓冲和对应的布局设置，不需要每次使用顶点缓冲时，重复设置其布局）
/// </summary>
class VertexArray
{
public:
	VertexArray();
	VertexArray(const class VertexArray& other) = delete;
	class VertexArray& operator = (const class VertexArray& other) = delete;
	~VertexArray();

	void AddLayout(const class VertexBuffer& vertexBuffer, const class VertexBufferLayout& vertexBufferLayout);

	void Bind() const;

private:
	unsigned int m_vertexArrayID;
};

