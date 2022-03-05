#pragma once

/// <summary>
/// ��������
/// ��ά���˶��㻺��Ͷ�Ӧ�Ĳ������ã�����Ҫÿ��ʹ�ö��㻺��ʱ���ظ������䲼�֣�
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

