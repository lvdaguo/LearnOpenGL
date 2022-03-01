#pragma once

/// <summary>
/// 顶点缓冲
/// </summary>
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;

	/// <summary>
	/// 获取缓冲个数
	/// </summary>
	unsigned int GetCount() const { return m_count; }

private:
	unsigned int m_bufferID;
	unsigned int m_count;
};

