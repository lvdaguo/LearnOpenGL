#pragma once

/// <summary>
/// ���㻺��
/// </summary>
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;

	/// <summary>
	/// ��ȡ�������
	/// </summary>
	unsigned int GetCount() const { return m_count; }

private:
	unsigned int m_bufferID;
	unsigned int m_count;
};

