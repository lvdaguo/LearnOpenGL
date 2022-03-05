#pragma once

/// <summary>
/// ���㻺��
/// </summary>
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	
	// �����˿������캯������Ϊ�ƶ�����ʱ�����һ�������������������������ݴ����ͷ�
	// Ӧ��ʹ��uniuqe_ptr��shadered_ptr���а�����ת�ƶ�������Ȩ���߽��й���
	IndexBuffer(const class IndexBuffer& other) = delete;
	// = ��ֵ�����ͬ��
	class IndexBuffer& operator = (const class IndexBuffer& other) = delete;

	~IndexBuffer();

	// ֻ���°󶨲������൱��ʹ�ô˶���ʹ����Ϻ��ý��
	// Ҫʹ����������ʱ�����°��������󼴿�
	// ���������Ǳ����һ����һ�����������Է���һ�����ǽ�opegl���н�����������Helper��̬����
	void Bind() const;

	/// <summary> ��ȡ������� </summary>
	unsigned int GetCount() const { return m_count; }

private:
	unsigned int m_bufferID;
	unsigned int m_count;
};

